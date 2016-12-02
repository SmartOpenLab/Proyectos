/*****************************************************************************
 * Designed to work with Arduino Uno, generic keypad (using a matrix pinout)
 * and generic fingerprint sensor (using Serial Communication)
 * 
 * @Author: Jorge Bote Albalá - Joriks <jorikst@gmail.com>
 *****************************************************************************/

#include <Keypad.h>
#include <Adafruit_Fingerprint.h>

//Define modules
bool subscribe();
bool unsubscribe();
bool control();
bool reset();
bool checkFingerprint();

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

void setup(){
  Serial.begin(9600);
  kpd.setDebounceTime(50);
  kpd.addEventListener(keypadEvent);
  
  finger.begin(57600);
}

void loop(){
  kpd.getKey();
}

void keypadEvent(KeypadEvent eKey){
  if(kpd.getState() == PRESSED){
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
  }
}

bool subscribe(){}
bool unsubscribe(){}
bool control(){}
bool reset(){}
bool checkFingerprint(){}

