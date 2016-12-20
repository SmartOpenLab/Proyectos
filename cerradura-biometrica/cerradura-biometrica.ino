/*****************************************************************************
 * Designed to work with Arduino Uno, generic keypad (using a matrix pinout)
 * and generic fingerprint sensor (using Serial Communication)
 * 
 * @Author: Jorge Bote Albalá - Joriks <jorikst@gmail.com>
 *****************************************************************************/

#define DEBUG

#include <Keypad.h>
#include <Adafruit_Fingerprint.h>

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
void showLed(int led_pin, int seconds, char* message);

/**************************** Relay Setup *************************************/
#define RELAY_PIN 10 //Relay to lock frame

/**************************** LEDs Setup *************************************/
#define WHITE_LED A0 //White Led for activity
#define GREEN_LED A1 //Red led for errors
#define RED_LED A2 //Green led for pass

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
// IN from sensor (GREEN wire to pin 11)
// OUT from arduino  (WHITE wire to pin 12)
SoftwareSerial mySerial(11, 12); //TTL Serial to communicate with fingerprint sensor

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); //Fingerprint variable

/**************************** IDs Setup *************************************/
int num_control_id = 10;
int last_control_id = 0;
int last_id = 10;

/**************************** Security Keys *************************************/
int key_a = 1111;
int key_b = 2222;
void setup(){
  Serial.begin(9600);
  kpd.setDebounceTime(50);
  kpd.addEventListener(keypadEvent);
  pinMode(WHITE_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  finger.begin(57600);
}

void loop(){
  kpd.getKey();
}

void keypadEvent(KeypadEvent eKey){
  if(kpd.getState() == PRESSED){
    digitalWrite(WHITE_LED,HIGH);
    #ifdef DEBUG
      Serial.println(eKey);
    #endif
    switch(eKey){
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
        checkFingerprint();
        break;
    }
    digitalWrite(WHITE_LED,LOW);
  }
}

bool subscribe(){//Usar código de colores para los leds
  int p = -1;
  #ifdef DEBUG
    Serial.print("Identifier ");
    Serial.println(last_id);
    Serial.println("Waiting for valid finger to enroll");
  #endif

  if(isFingerprintControl()){
    showLed(GREEN_LED,1,"Correct Control Fingerprint");
    if(getFingerprint()){
      showLed(GREEN_LED,1,"Correct Fingerprint");
      int password;
      if(getPassword(password)){
          finger.storeModel(last_id++);
          if(p == FINGERPRINT_OK){
            #ifdef DEBUG
              Serial.print("Insertada Huella(");
              Serial.print(last_id-1);
              Serial.print(",");
              Serial.print(password);
              Serial.println(")");
            #endif
            //ingresar en array 
            showLed(GREEN_LED,2,"Insertada huella correctamente");
          }
      }
      else
        showLed(RED_LED,2, "Error: PASSWORD did not Match");
    }
    else
      showLed(RED_LED,2, "Error: FINGERPRINT did not match");
  }
  else
    showLed(RED_LED,5, "Error: No CONTROL Fingerprint");
bool unsubscribe(){
  int p = -1;
  #ifdef DEBUG
    Serial.print("Identifier ");
    Serial.println(last_id);
    Serial.println("Waiting for valid finger to enroll");
  #endif

  if(isFingerprintControl()){
    showLed(GREEN_LED,1,"Correct Control Fingerprint");
    uint16_t finger_id = checkFingerprint();
    if(finger_id =! -1 && finger_id > num_control_id){
      p = finger.deleteModel(finger_id);
      if(p == FINGERPRINT_OK){
        showLed(GREEN_LED,2,"Finger deleted");
        //borrar del array
      }
    }
    else
      showLed(RED_LED,2,"Error: Can not delete a control fingerprint");
  }
  else
    showLed(RED_LED,5, "Error: No CONTROL Fingerprint");
}
bool control(){}
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
  }while(num_checks<3);  
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
  if(finger_id>=0 && finger_id<last_control_id)
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
  Serial.println("Finger Obtaining");
  if(getFingerImage() == FINGERPRINT_OK){
    Serial.println("Paso 1");
    p = finger.image2Tz(1);
    if (p != FINGERPRINT_OK)  return false;
    showLed(GREEN_LED,1,"First print OK, Remove and put your finger back");
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
  int num_keys = 0;
  int pass = 0, pass2 = 0;
  while(num_keys < 4){
    pass = pass*10;
    pass += (kpd.waitForKey()-48);
    num_keys++;
  }
  num_keys = 0;
  while(num_keys < 4){
    pass2 = pass2*10;
    pass2 += (kpd.waitForKey()-48);    
    num_keys++;
  }
  if(pass == pass2){
    password = pass;
    return true;
  }
  return false;
}
void showLed(int led_pin, int seconds, char* message){
    #ifdef DEBUG
      Serial.println(message);
    #endif
    digitalWrite(led_pin,HIGH);
    delay(seconds*1000);
    digitalWrite(led_pin,LOW);
}

