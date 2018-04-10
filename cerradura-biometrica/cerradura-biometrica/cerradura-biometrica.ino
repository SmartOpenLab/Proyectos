/*****************************************************************************
 * Designed to work with Arduino Uno, generic keypad (using a matrix pinout),
 * generic fingerprint sensor (using Serial Communication) and OLED display
 * 128x64 size (using i2c bus)
 * 
 * @Author: Jorge Bote Albalá - Joriks <jorikst@gmail.com>
 *****************************************************************************/

#define DEBUG

#define OLED_MODE

#if !defined LED_MODE && !defined OLED_MODE
  #error "You need to specific at least one mode of show information"
#endif

#include <Keypad.h>
#include <Adafruit_Fingerprint.h>
#include "U8glib.h"
#include <EEPROM.h>

//Define main modules
bool subscribe();
bool unsubscribe();
bool control();
bool reset();
void checkAccess();

//Define modules
void subscribe_control();
void unsubscribe_control();
uint8_t getFingerImage();
bool getFingerPrint();
int checkFingerID();
bool isFingerControl();
int16_t getPassword();
int16_t checkPassword();
void factoryReset();

void showLed(int led_pin, int seconds, char* message);
void draw(char* m);

/**************************** Relay Setup *************************************/
#define RELAY_PIN A3 //Relay to lock frame

/**************************** LEDs Setup *************************************/
#define WHITE_LED A0 //White Led for activity
#define GREEN_LED A1 //Red led for errors
#define RED_LED A2 //Green led for pass

/**************************** OLED Setup *************************************/
#ifdef OLED_MODE
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
#endif

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
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(WHITE_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(RELAY_PIN,OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  finger.begin(57600);
  #ifdef OLED_MODE
    u8g.setFont(u8g_font_unifont);
    u8g.setColorIndex(1);
  #endif
  control_id = EEPROM.read(645);
  if(control_id==255)
    control_id=0;
  user_id = EEPROM.read(646);
  if(user_id==255)
    user_id=0;

  #ifdef DEBUG
    Serial.println(control_id);
    Serial.println(user_id);
  #endif
}

void loop(){
  char op = kpd.waitForKey();
  if(kpd.getState() == PRESSED){
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
      case '*':
        checkAccess();
        break;
    }
  }
}

bool subscribe(){
  unsigned int user_pass = 0;
  char buf[4];
  sprintf(buf,"%d",user_id);
  
  showLed(WHITE_LED,1,"Introduzca una  huella de       control");
  if(isFingerControl()){
    if(getFingerPrint()){
      showLed(GREEN_LED,1,"Huella Correcta");
      user_pass = checkPassword();
      if(user_pass != -1){
        finger.storeModel(user_id);
        #ifdef DEBUG 
          Serial.print("Agregado Usuario("); 
          Serial.print(user_id); 
          Serial.print(","); 
          Serial.print(user_pass); 
          Serial.println(")"); 
        #endif
        EEPROM.write((user_id*4)+3,user_pass%10);
        user_pass = user_pass/10;
        EEPROM.write((user_id*4)+2,user_pass%10);
        user_pass = user_pass/10;
        EEPROM.write((user_id*4)+1,user_pass%10);
        user_pass = user_pass/10;
        EEPROM.write((user_id*4)+0,user_pass%10);
        user_id++;
        EEPROM.write(646,user_id);
        #ifdef OLED_MODE
          u8g.firstPage();
          do {  
            u8g.drawStr( 0, 15, "Usuario agregado");
            u8g.drawStr( 0, 30, buf);
          } while( u8g.nextPage() );
          delay(5000);
          u8g.firstPage();
          while( u8g.nextPage() );
        #endif
      }
    }
    else
      showLed(RED_LED,2, "ERROR:          Las huellas NO  coinciden");
  }
  else
    showLed(RED_LED,5, "ERROR:          NO es huella de control");
}

bool unsubscribe(){
  showLed(WHITE_LED,1,"Introduzca una  huella de       control");
  if(isFingerControl()){
    showLed(WHITE_LED,3,"Introduzca una  huella a borrar");
    int finger_id = checkFingerID();
    if(finger_id != -1){
      if(finger_id > num_control_id && finger_id <= user_id){
        if(finger.deleteModel(finger_id) == FINGERPRINT_OK){
          EEPROM.write((finger_id*4)+0,255);
          EEPROM.write((finger_id*4)+1,255);
          EEPROM.write((finger_id*4)+2,255);
          EEPROM.write((finger_id*4)+3,255);
          showLed(GREEN_LED,3,"Usuario borrado correctamente");
        }
      }
      else
        showLed(RED_LED,3,"Usuario de      control NO borrado");
    }
    else
      showLed(RED_LED,3,"Usuario         NO borrado");
  }
  else
    showLed(RED_LED,5, "ERROR:          NO es huella de control");
}

bool control(){
  char option = kpd.waitForKey();
    
  if(option != 'D'){
    bool correct_control = false;
    
    if(control_id == 0){
      showLed(GREEN_LED,3,"Inserta la      primera clave"); 
      int16_t pass = getPassword(); 
      if(pass == key_a){ 
        showLed(GREEN_LED,3,"Inserta la      segunda clave"); 
        pass = getPassword(); 
        if(pass == key_b) 
          correct_control = true;
        else
          showLed(RED_LED,3,"Clave Incorrecta");
      }
      else
        showLed(RED_LED,3,"Clave Incorrecta");
    }
    else{
      showLed(WHITE_LED,1,"Introduzca una  huella de       control");
      if(isFingerControl()){
        correct_control = true;
        showLed(GREEN_LED,3,"Huella de       control Correcta");
      }
      else
      showLed(RED_LED,5, "ERROR:          NO es huella de control");
    }
    if(correct_control){
      if(option == 'A')
        subscribe_control();
      else if(option == 'B')
        unsubscribe_control();
    }
  }
  else
    reset();
}

bool reset(){
  showLed(GREEN_LED,5,"Identificar por 1)Huella        2)Clave Maestra");
  char op = kpd.waitForKey();
  if(op == '1'){
    showLed(WHITE_LED,1,"Primera huella  de control");
    if(isFingerControl()){
      showLed(WHITE_LED,1,"Segunda huella  de control");
      if(isFingerControl())
        factoryReset();
      else
        showLed(RED_LED,5, "ERROR:          NO es huella de control");
    }
    else
      showLed(RED_LED,5, "ERROR:          NO es huella de control");
  }
  else{
    if(op == '2'){
      showLed(GREEN_LED,3,"Inserta la      primera clave");
      int16_t pass = getPassword();
      if(pass == key_a){
        showLed(GREEN_LED,3,"Inserta la      segunda clave");
        pass = getPassword();
        if(pass == key_b)
          factoryReset();
        else
          showLed(RED_LED,5, "ERROR:          NO es Clave     Maestra");
      }
      else
        showLed(RED_LED,5, "ERROR:          NO es Clave     Maestra");
    }
  }
}

void subscribe_control(){
  int16_t user_pass = 0;

  if(getFingerPrint()){
    showLed(GREEN_LED,1,"Huella Correcta");
    user_pass = checkPassword();
    if(user_pass != -1){
      if(control_id < num_control_id){
        finger.storeModel(control_id);
        #ifdef DEBUG 
          Serial.print("Añadido Usuario("); 
          Serial.print(control_id); 
          Serial.print(","); 
          Serial.print(user_pass); 
          Serial.println(")"); 
        #endif
        EEPROM.write((control_id*4)+3,user_pass%10);
        user_pass = user_pass/10;
        EEPROM.write((control_id*4)+2,user_pass%10);
        user_pass = user_pass/10;
        EEPROM.write((control_id*4)+1,user_pass%10);
        user_pass = user_pass/10;
        EEPROM.write((control_id*4)+0,user_pass%10);
        control_id++;
        EEPROM.write(645,control_id);
        showLed(GREEN_LED,2,"Usuario agregado");
      }
      else
        showLed(RED_LED,5,"Limite de       usuarios de     control");
    }
  }
  else
    showLed(RED_LED,2, "ERROR:          Las huellas NO  coinciden");
}

void unsubscribe_control(){
  showLed(WHITE_LED,3,"Introduzca una  huella a borrar");
  int finger_id = checkFingerID(); 
  if(finger_id != -1){ 
    if(finger_id >= 0 && finger_id <= control_id){ 
      if(finger.deleteModel(finger_id) == FINGERPRINT_OK){
        EEPROM.write((finger_id*4)+0,255);
        EEPROM.write((finger_id*4)+1,255);
        EEPROM.write((finger_id*4)+2,255);
        EEPROM.write((finger_id*4)+3,255);
        showLed(GREEN_LED,3,"Usuario de      control borrado");
      }
    } 
    else 
      showLed(RED_LED,3,"Usuario normal  NO borrado"); 
  }
  else 
    showLed(RED_LED,3,"Usuario NO      borrado"); 
}

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
  showLed(GREEN_LED,4,"Pon el dedo en  el sensor");
  p = getFingerImage();
  if(p == FINGERPRINT_OK){
    p = finger.image2Tz(1);
    if(p != FINGERPRINT_OK) return false;
    showLed(GREEN_LED,2,"Huella correcta,retira el dedo");
    while(finger.getImage() != FINGERPRINT_NOFINGER);
    showLed(GREEN_LED,4,"Vuelve a poner  el dedo");
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
    if(isdigit(key)){
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
  showLed(WHITE_LED,3,"Inserta una     Clave");
  pass = getPassword();
  if(pass != -1){
    showLed(GREEN_LED,3,"Repite la Clave");
    pass2 = getPassword();
    if(pass2 != -1){
      if(pass == pass2){
        showLed(GREEN_LED,3,"Clave Correcta");
        return pass;
      }
      else
          showLed(RED_LED,3,"ERROR:          Las Claves NO   coinciden");
    }
    else
      showLed(RED_LED,3,"ERROR:          Fallo al repetirClave");
  }
  else
    showLed(RED_LED,3,"ERROR:          Fallo al        insertar Clave");
  return -1;
}

void checkAccess(){
  int id = checkFingerID();
  if(id != -1){
    digitalWrite(RELAY_PIN,LOW);
    delay(100);
    digitalWrite(RELAY_PIN,HIGH);
    showLed(GREEN_LED,3,"Acceso Permitido");
  }
  else{
    showLed(WHITE_LED,3,"Introduce tu ID (3 digitos)");
    uint8_t i = 0;
    uint16_t id = 0;
    char key = 0;
    while(i < 3){
      key = kpd.waitForKey();
      if(isdigit(key)){
        id = id*10 + (key-48);
        i++;
      }        
    }
    int16_t pass = EEPROM.read(id*4+0);
    pass = pass*10 + EEPROM.read(id*4+1);
    pass = pass*10 + EEPROM.read(id*4+2);
    pass = pass*10 + EEPROM.read(id*4+3);
    showLed(WHITE_LED,3,"Introduce tu    clave");
    if(pass == getPassword() && pass != 0){
      digitalWrite(RELAY_PIN,LOW);
      showLed(GREEN_LED,3,"Acceso Permitido");
      digitalWrite(RELAY_PIN,HIGH);
    }
    else
      showLed(RED_LED,3,"Acceso Denegado");
  }
}

void factoryReset(){
  char op = 0;
  showLed(GREEN_LED,2,"Desea restaurar de fabrica?     1)SI    2)NO");
  op = kpd.waitForKey();
  if(op == '1'){
    int i = 0;
    while(i<161){
      if(finger.deleteModel(i) == FINGERPRINT_OK){
        EEPROM.write(i*4+0,255);
        EEPROM.write(i*4+1,255);
        EEPROM.write(i*4+2,255);
        EEPROM.write(i*4+3,255);
        #ifdef DEBUG
          Serial.print("Borrado Usuario: ");
          Serial.println(i);
        #endif
        i++;
      }
    }
    EEPROM.write(645,0);
    control_id = 0;
    EEPROM.write(646,10);
    user_id = 10;
    showLed(GREEN_LED,3,"Restauracion    Completada");
  }
  else
    showLed(RED_LED,3,"Borrado         Cancelado");
}

void showLed(int led_pin, int seconds, char* message){
    #ifdef DEBUG
      Serial.println(message);
    #endif
    #ifdef OLED_MODE
      u8g.firstPage();
      do {  
        draw(message);
      } while( u8g.nextPage() );
    #endif
    #ifdef LED_MODE
      digitalWrite(led_pin,HIGH);
    #endif
    delay(seconds*1000);
    #ifdef OLED_MODE
      u8g.firstPage();
      while( u8g.nextPage() );
    #endif
    #ifdef LED_MODE
      digitalWrite(led_pin,LOW);
    #endif
}

#ifdef OLED_MODE
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
#endif
