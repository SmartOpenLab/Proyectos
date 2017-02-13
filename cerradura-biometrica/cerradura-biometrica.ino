/*****************************************************************************
 * Designed to work with Arduino Uno, generic keypad (using a matrix pinout)
 * and generic fingerprint sensor (using Serial Communication)
 * 
 * @Author: Jorge Bote Albalá - Joriks <jorikst@gmail.com>
 *****************************************************************************/

#define DEBUG

#include <Keypad.h>
#include <Adafruit_Fingerprint.h>
#include "U8glib.h"

//Define main modules
bool subscribe();
bool unsubscribe();
bool control();
bool reset();
void checkAccess();

//Define modules
uint8_t getFingerImage();
bool getFingerPrint();
int checkFingerID();
bool isFingerControl();
int16_t getPassword();
int16_t checkPassword();

void showLed(int led_pin, int seconds, char* message);
void draw(char* m);

/**************************** Relay Setup *************************************/
#define RELAY_PIN A3 //Relay to lock frame

/**************************** LEDs Setup *************************************/
#define WHITE_LED A0 //White Led for activity
#define GREEN_LED A1 //Red led for errors
#define RED_LED A2 //Green led for pass

/**************************** OLED Setup *************************************/
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);


/************************** Keypad Setup *************************************/
const byte ROWS = 4; //Number of rows
const byte COLS = 4; //Number of columns

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};//Matrix of keys

//connect first pinout of the kpd to 2 and last pinout to 9
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); //Keypad variable

/************************** Fingerprint Setup *************************************/
// IN from sensor (YELLOW wire to pin 10)
// OUT from arduino  (WHITE wire to pin 11)
SoftwareSerial mySerial(10, 11); //TTL Serial to communicate with fingerprint sensor

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); //Fingerprint variable

/**************************** IDs Setup *************************************/
int num_control_id = 10;
int control_id = 0;
int user_id = 10;

/**************************** Security Keys *************************************/
int key_a = 1111;
int key_b = 2222;

void setup(){
  Serial.begin(9600);
  kpd.setDebounceTime(50);
  pinMode(WHITE_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(RELAY_PIN,OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  finger.begin(57600);
  u8g.setFont(u8g_font_unifont);
  u8g.setColorIndex(1);
}

void loop(){
  char op = kpd.waitForKey();
  if(kpd.getState() == PRESSED){
    digitalWrite(WHITE_LED,HIGH);
    switch(op){
      case 'A':
        subscribe();
        break;
      case 'B':
        unsubscribe();
        break;
      case 'C':
        control();
        break;
      case 'D':
        reset();
        break;
      case '*':
        checkAccess();
        break;
    }
    digitalWrite(WHITE_LED,LOW);
  }
}

bool subscribe(){
  unsigned int user_pass = 0;
  
  showLed(WHITE_LED,1,"Introduzca una huella de control");
  if(isFingerControl()){
    if(getFingerPrint()){
      showLed(GREEN_LED,1,"Huella Correcta");
      user_pass = checkPassword();
      if(user_pass != -1){
        finger.storeModel(user_id);
        #ifdef DEBUG 
          Serial.print("Añadido Usuario("); 
          Serial.print(user_id); 
          Serial.print(","); 
          Serial.print(user_pass); 
          Serial.println(")"); 
        #endif
        user_id++;
        showLed(GREEN_LED,2,"Usuario agregado");
      }
    }
    else
      showLed(RED_LED,2, "Error: Las huellas no coinciden");
  }
  else
    showLed(RED_LED,5, "Error: No es huella de control");
}
bool unsubscribe(){}
bool control(){}
bool reset(){}

uint8_t getFingerImage(){
  uint8_t p = -1;
  uint8_t check = 0;
  do{
    unsigned long prev_millis = millis();
    do{
      p = finger.getImage();
    }while(p != FINGERPRINT_OK && (millis() - prev_millis) < 3000);
    check++;
  }while(p != FINGERPRINT_OK && check < 3);
  return p;
}

bool getFingerPrint(){
  uint8_t p;
  showLed(GREEN_LED,4,"Pon el dedo en el sensor");
  p = getFingerImage();
  if(p == FINGERPRINT_OK){
    p = finger.image2Tz(1);
    if(p != FINGERPRINT_OK) return false;
    showLed(GREEN_LED,2,"Huella correcta, retira el dedo");
    while(finger.getImage() != FINGERPRINT_NOFINGER);
    showLed(GREEN_LED,4,"Vuelve a poner el dedo");
    p = getFingerImage();
    if(p == FINGERPRINT_OK){
      p = finger.image2Tz(2);
      if(p != FINGERPRINT_OK) return false;
      p = finger.createModel();
      if(p == FINGERPRINT_OK) return true;
    }
  }
  return false;
}

int checkFingerID(){
  uint8_t p;
  p = getFingerImage();
  if(p != FINGERPRINT_OK) return -1;
  p = finger.image2Tz();
  if(p != FINGERPRINT_OK) return -1;
  p = finger.fingerFastSearch();
  if(p != FINGERPRINT_OK) return -1;
  return finger.fingerID;
}

bool isFingerControl(){
  int finger_id = checkFingerID();
  if(finger_id >= 0 && finger_id < control_id)
    return true;
  return false;
}

int16_t getPassword(){
  uint8_t num_keys = 0;
  int16_t password = 0;
  char key = 0;
  while(num_keys < 4 && password != -1){
    key = kpd.waitForKey();
    if(key > 47 && key < 58){
      password = password * 10;
      password += (key-48);
      num_keys++;
    }
    else
      password = -1;
  }
  return password;
}

int16_t checkPassword(){
  int16_t pass = 0;
  int16_t pass2 = 0;
  showLed(WHITE_LED,3,"Inserta una Clave");
  pass = getPassword();
  if(pass != -1){
    showLed(GREEN_LED,3,"Repite la Clave");
    pass2 = getPassword();
    if(pass2 != -1){
      if(pass == pass2){
        showLed(GREEN_LED,3,"Las Claves son iguales");
        return pass;
      }
      else
          showLed(RED_LED,3,"ERROR: Las Claves no coinciden");
    }
    else
      showLed(RED_LED,3,"ERROR: Fallo al repetir Clave");
  }
  else
    showLed(RED_LED,3,"ERROR: Fallo al insertar Clave");
  return -1;
}

void checkAccess(){
  int id = checkFingerID();
  if(id != -1){
    digitalWrite(RELAY_PIN,LOW);
    showLed(GREEN_LED,3,"Acceso Permitido");
    digitalWrite(RELAY_PIN,HIGH);
  }
  else
    showLed(RED_LED,3,"Acceso Denegado");
}

void showLed(int led_pin, int seconds, char* message){
    #ifdef DEBUG
      Serial.println(message);
    #endif
    u8g.firstPage();
    do {  
      draw(message);
    } while( u8g.nextPage() );
    digitalWrite(led_pin,HIGH);
    delay(seconds*1000);
    u8g.firstPage();
    while( u8g.nextPage() );
    digitalWrite(led_pin,LOW);
}

void draw(char* m){
  int i = 0;
  char message[51] = "";
  strcpy(message,m);
  char message2[17] = "";
  while(strlen(message) > 16){
    strncpy(message2,message,16);
    strcpy(message,message+16);
    u8g.drawStr( 0, 15+i, message2);    
    i = i + 15;
  }
  u8g.drawStr( 0, 15+i, message);
}
