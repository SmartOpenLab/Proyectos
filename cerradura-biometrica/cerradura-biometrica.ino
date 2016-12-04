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
bool checkFingerprint();

//Define modules
bool isFingerprintControl();
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

bool subscribe(){}
bool unsubscribe(){}
bool control(){}
bool reset(){}
bool checkFingerprint(){}
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

