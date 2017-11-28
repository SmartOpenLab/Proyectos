#define APAGADO 0
#define CaraUNO 1
#define CaraDOS 2
#define STARTBOT 3
#define RESET 4
#define BottomTime 7

#define ONCaraUNO 5
#define ONCaraDOS 6

boolean Insolar = false;
boolean Setting = false;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long Interval = 0;

unsigned int Cara = 0;

unsigned int segundos = 0;

void setup() {

  Serial.begin(9600);

  pinMode(STARTBOT, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
  pinMode(APAGADO, INPUT_PULLUP);
  pinMode(CaraUNO, INPUT_PULLUP);
  pinMode(CaraDOS, INPUT_PULLUP);
  pinMode(BottomTime, INPUT_PULLUP);
  
  pinMode(ONCaraUNO, OUTPUT);
  pinMode(ONCaraDOS, OUTPUT);
  
  digitalWrite(ONCaraUNO,LOW);
  digitalWrite(ONCaraDOS,LOW);
}

void loop() {
  
  if(!Setting){
    insolateTime();
    if(digitalRead(CaraUNO) == LOW){
      Cara = 1;
      Setting = true;
    }
    if(digitalRead(CaraDOS) == LOW){
      Cara = 2;
      Setting = true;
    }
    if(digitalRead(BottomTime) == LOW){
      Interval += 5000;
     }
  }


insolar();
}

void insolateStart(){
  if(digitalRead(STARTBOT) == LOW){
    Serial.println(digitalRead(STARTBOT));
    if(Setting){
      if(Cara == 1){
        digitalWrite(ONCaraUNO,HIGH);
      }
      if(Cara == 2){
        digitalWrite(ONCaraUNO,HIGH);
        digitalWrite(ONCaraDOS,HIGH);
      }
      Insolar = true;
      previousMillis = millis();
    }
  }
}

void insolar(){
    insolateStart();
    if(Insolar){
     currentMillis = millis();
      if(currentMillis - previousMillis >= Interval){
        digitalWrite(ONCaraUNO,LOW);
        digitalWrite(ONCaraDOS,LOW);
        Insolar = false;
        Setting = false;
      }
  }
}

void insolateTime(){
  if(digitalRead(BottomTime) == LOW){
  if(segundos < 150) // CORREGIDO Si el boton ha sido pulsado, aumentamos los segundos en una unidad
    {
      segundos = segundos + 10;
    }
  }
  else segundos = 0;  
}
