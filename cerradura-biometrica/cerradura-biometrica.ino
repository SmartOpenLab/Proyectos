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
uint16_t checkFingerprint();

//Define modules
bool isFingerprintControl();
uint8_t getFingerImage();
bool getFingerprint();
bool getPassword(int &password);
bool getKeyPass(int &password);
void checkAccess();
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
bool get_user_pass = false;

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
  if(get_user_pass){
    int user_pass = 0;
    if(getPassword(user_pass)){
      finger.storeModel(user_id);
      #ifdef DEBUG
        Serial.print("Añadido Usuario(");
        Serial.print(user_id);
        Serial.print(",");
        Serial.print(user_pass);
        Serial.println(")");
      #endif
      user_id++;
      //ingresar en array 
      showLed(GREEN_LED,2,"Usuario Añadido Correctamente");
    }
    get_user_pass = false;
  }
}

bool subscribe(){
  int pass_a = 0;
  int pass_b = 0;
  int user_pass = 0;
  
  showLed(WHITE_LED,1,"Introduzca una huella de control");
  if(control_id == 0 || isFingerprintControl()){
    if(control_id == 0){
      if(getKeyPass(pass_a) && getKeyPass(pass_b) && pass_a == key_a && pass_b == key_b)
        showLed(GREEN_LED,1,"Claves Maestras Correctas");
      else{
        showLed(RED_LED,1,"Error: Las Claves Maestras no coinciden");
        return false;
      }
    }
    else
      showLed(GREEN_LED,1,"Huella de control Correcta");

    if(getFingerprint()){
      showLed(GREEN_LED,1,"Huella Correcta");
      get_user_pass = true;
    }
    else
      showLed(RED_LED,2, "Error: Las huellas no coinciden");
  }
  else
    showLed(RED_LED,5, "Error: No es huella de control");
bool unsubscribe(){
  int p = -1;
  #ifdef DEBUG
    Serial.println("Esperando huella para borrar");
  #endif

  if(isFingerprintControl()){
    showLed(GREEN_LED,1,"Huella de control Correcta");
    uint16_t finger_id = checkFingerprint();
    if(finger_id =! -1 && finger_id > num_control_id){
      p = finger.deleteModel(finger_id);
      if(p == FINGERPRINT_OK){
        showLed(GREEN_LED,2,"Usuario Borrado");
        //borrar del array
      }
    }
    else
      showLed(RED_LED,2,"ERROR: No se puede borrar una huella de control");
  }
  else
    showLed(RED_LED,5, "ERROR: No es huella de control");
}

bool control(){
  int p = -1;
  char option = kpd.waitForKey();
  #ifdef DEBUG
    Serial.println("Waiting for valid finger");
  #endif
  
  if(option == 'A'){
      if(getFingerprint()){
      showLed(GREEN_LED,1,"Correct Fingerprint");
      int password;
      if(getPassword(password)){
        finger.storeModel(control_id++);
        #ifdef DEBUG
          Serial.print("Insertada HuellaControl(");
          Serial.print(control_id-1);
          Serial.print(",");
          Serial.print(password);
          Serial.println(")");
        #endif
        showLed(GREEN_LED,2,"Insertada huella de control correctamente");
      }
      else
        showLed(RED_LED,2, "Error: PASSWORD did not Match");
    }
    else
      showLed(RED_LED,2, "Error: FINGERPRINT did not match");
  }
}

bool reset(){}
uint16_t checkFingerprint(){
  unsigned long prev_millis = 0;
  uint8_t num_checks = 0;
  uint8_t p;
  do{
    prev_millis = millis();
    do{
      p = finger.getImage();
    }while((p != FINGERPRINT_OK) && ((millis() - prev_millis) <= 3000));
    if(p != FINGERPRINT_OK){
      num_checks++;
      #ifdef DEBUG
        Serial.print("Check number ");
        Serial.println(num_checks);
      #endif
    }
  }while(num_checks<3 && p != FINGERPRINT_OK);  
  
  if(p == FINGERPRINT_OK){
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)  return -1;
  
    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)  return -1;
    return finger.fingerID; 
  }
  return -1;
  //Leer huella desde el sensor
  //lee 3 huellas, si falla, encender led rojo y sonar zumbador y pedir clave numerica
}
bool isFingerprintControl(){
  uint16_t finger_id = checkFingerprint();
  if(finger_id>=0 && finger_id<control_id)
    return true;
  return false;
}

uint8_t getFingerImage(){
  unsigned long prev_millis = millis();
  uint8_t num_checks = 0;
  uint8_t p;
  do{
    do{
      p = finger.getImage();
    }while(p != FINGERPRINT_OK && (millis() - prev_millis) <= 3000);
    if(p != FINGERPRINT_OK)
      num_checks++;
  }while(num_checks<3 && p != FINGERPRINT_OK);
  return p;
}

bool getFingerprint(){
  uint8_t p;
  showLed(GREEN_LED,4,"Pon el dedo en el sensor");
  if(getFingerImage() == FINGERPRINT_OK){
    Serial.println("Paso 1");
    p = finger.image2Tz(1);
    if (p != FINGERPRINT_OK)  return false;
    showLed(GREEN_LED,4,"Huella correcta, quita y vuelve a poner el dedo");
    while (p != FINGERPRINT_NOFINGER) {
      p = finger.getImage();
    }

    if(getFingerImage() == FINGERPRINT_OK){
      Serial.println("Paso 2");
      p = finger.image2Tz(2);
      if (p != FINGERPRINT_OK)  return false;
      p = finger.createModel();
      if(p == FINGERPRINT_OK){
        Serial.println("Paso 3");
        return true;
      }
    }
  }
  return false;
}

bool getPassword(int &password){
  int pass = 0, pass2 = 0;
  showLed(WHITE_LED,3,"Inserta una Clave");
  if(getKeyPass(pass)){
    showLed(GREEN_LED,3,"Repite la Clave");
    if(getKeyPass(pass2)){
      if(pass == pass2){
        password = pass;
        showLed(GREEN_LED,3,"Las Claves son iguales");
        return true;
      }
      else
          showLed(RED_LED,3,"ERROR: Las Claves no coinciden");
    }
    else
      showLed(RED_LED,3,"ERROR: Fallo al insertar Clave");
  }
  else
    showLed(RED_LED,3,"ERROR: Fallo al insertar Clave");
  return false;
}

bool getKeyPass(int &password){
  int num_keys = 0;
  int pass = 0;
  char key = 0;
  while(num_keys < 4){
    key = kpd.waitForKey();
    if(key < 48 && key > 57)
      return false;
    pass = pass*10;
    pass += (key-48);
    num_keys++;
  }
  password = pass;
  return true;
}

void checkAccess(){
  uint16_t id = checkFingerprint();
  if(id != -1){
    digitalWrite(RELAY_PIN,LOW);
    showLed(GREEN_LED,3,"Acceso Permitido");
    digitalWrite(RELAY_PIN,HIGH);
  }
  else{
    showLed(RED_LED,3,"Acceso Denegado");
  }
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
