//
// OPEN SOUND METER V1
//---------------------******--------------------------//
//
// Include:
//    - Lecture of the value of the analog input pin.
//    - Wifi communication using MQTT protocol.
//    - Server upload to: io.adafruit.com
//    
// Based on:
//    - Wemos ESP8266 hardware.
//    - Adafruit resources and community.
//    - Arduino online open community. Thank you all!
//
// Licensed under Creative Commons (SH-BY-NC). @AGordiGuerrero
//
//
// Jaime Borrallo Rivera
// 
// @jaborrall 
// 
//
// 
// Antonio Gordillo Guerrero
// anto@unex.es
// @AGordiGuerrero
// 
// Smart Open Lab. Escuela Politécnica de Cáceres. Universidad de Extremadura.
// @SolEpcc
// www.smartopenlab.com
//--------------------******---------------------------//



// Libraries
#include <ESP8266WiFi.h> 
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>                                                                   
#include <ArduinoOTA.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
//#define DEBUG                                                                        //uncomment for serial port debug

/************************* WiFi Access Point *********************************/
#define WLAN_SSID     "AndroidAP"//"MiFibra-A7EF"                                                   // Wi-Fi parameters
#define WLAN_PASS     "crht1214"//"6jNVTUYW"   

/************************* Server Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"                                              // Server parameters using io.adafruit.com
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "Jimmy_Jazz"
#define AIO_KEY         "78ee0365382d4da282ca19727450df2f"

// Variable
int sensorPIN = A0,sample,i=0;                                                         
int tiempo_de_envio=29999;
unsigned long tiempo_inicial,tiempo_final=0,tiempo_medida,tiempo_desde_ult_medida;
unsigned long periodo_medidas=125;
float volts,dB,promedio,suma=0;

WiFiClient client;                                                                     

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY); // Parameters to conect to server as client

Adafruit_MQTT_Publish muestra = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Laeq"); // Parameters for sending data, we send to the server folder: /feeds/LAeq

                                                              
void setup()
{
  #ifdef DEBUG
    Serial.begin(115200);                                                               // Serial port init
    Serial.println("Adafruit MQTT");                                                 
    Serial.println(); Serial.println();                                              
    Serial.print("Connected to: ");                                                    
    Serial.println(WLAN_SSID);                                                       
  #endif
  
  pinMode(D4,OUTPUT);                                                                  // D4 as output for the LED blink
  WiFi.mode(WIFI_STA);                                                                 // Security type
  WiFi.begin(WLAN_SSID, WLAN_PASS);                                                    // Wi-Fi connection. If no connection wait for 0,5s and retry
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    #ifdef DEBUG
      Serial.print(".");                                                               
    #endif
    
    }
    ArduinoOTA.setPassword((const char *)"1234");                                      // OTA password, by default "1234"
    ArduinoOTA.begin();                                                                
    
    #ifdef DEBUG
      Serial.println();                                                                
      Serial.println("WiFi connected");                                                 
      Serial.println("IP: "); 
      Serial.println(WiFi.localIP());                 
    #endif
}

void loop()
{
 ArduinoOTA.handle();                                                                  // OTA handling 
 medida();                                                                             // Measure

 envio();                                                                              // Send
}


void medida()
{
  tiempo_inicial=millis();                                                             // Saving current time
  
  if((tiempo_inicial - tiempo_final) > periodo_medidas) {                              // Measure if sampling time has come
    sample = analogRead(sensorPIN);                                                    // Read analog port
    volts = ((sample * 3.3) / 1023);                                                   // Voltage conversion
    dB=-(102.48*pow(volts,6))+(895*pow(volts,5))-(3201.1*pow(volts,4))+(5997.5*pow(volts,3))-(6211.5*pow(volts,2))+(3401.8*volts)-694.87;// Formula from calibration
    suma+=dB;                                                                          // Suming samples
    i++;                                                                               // increase measure index
    tiempo_final=millis();                                                             // Saving last measure time
    }
}


void envio()
{
  tiempo_medida=millis();                                                              // Saving current time
  if((tiempo_medida-tiempo_desde_ult_medida)>tiempo_de_envio) {                        // Send if sending toiem has come
    MQTT_connect();                                                                    // Connnecting to server
    promedio=suma/i;                                                                   // Averaging                                                                       
    if(muestra.publish(promedio)) {                                                    // If we send the sample we blink the LED
       
      digitalWrite(D4, HIGH);                                                         
      delay(10);
      digitalWrite(D4, LOW);
    
      #ifdef DEBUG
        Serial.println("Sample sent.");                                             
        Serial.print("Time from last measure (ms): ");                          
        Serial.println(tiempo_medida-tiempo_desde_ult_medida);                         
        Serial.print("Measured value (LAeq): ");                                          
        Serial.println(promedio);                                                      
      #endif

      i=0;                                                                           // Variable restart
      promedio=0;                                                                     
      suma=0; 
      }
    tiempo_desde_ult_medida=millis();                                                  // Saving last measure time
    }
}   


void MQTT_connect() 
{
  int8_t ret;

  if (mqtt.connected()) {                                                              // If we connect return to main code...
    return;                                                                            
    }
    
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {                                                // If no connection, retry...
         
    #ifdef DEBUG
      Serial.println(mqtt.connectErrorString(ret));                              
      Serial.println("Reconnecting MQTT...");                                   
    #endif
         
    mqtt.disconnect();                                                               // Wait for a second and retry
    delay(1000);  
    retries--;
    }

  #ifdef DEBUG
    Serial.println("MQTT Connected.");                                             
  #endif
  
  digitalWrite(D4, HIGH);                                                              // Make an slow LED blink
  delay(500);
  digitalWrite(D4 , LOW);
}
