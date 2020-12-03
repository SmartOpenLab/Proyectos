# OpenSoundMeter

Design of a **continuous-measurement sound-level meter with Wi-Fi connectivity**, to be integrated into the sensor network of the Escuela Politécnica de Cáceres, [SmartPoliTech](http://smartpolitech.unex.es/).

![](https://raw.githubusercontent.com/AGordiGuerrero/OpenSoundMeter/master/photos/9.jpg)

You can find both the printed circuit board (PCB) that performs the preamplification and the necessary weightings for the adaptation of the signals captured through the microphone and the Arduino code.

![](https://raw.githubusercontent.com/AGordiGuerrero/OpenSoundMeter/master/photos/6-1.jpg)

Average acoustic pressure signals are captured by the analog input of the Wemos D1 Mini board in order to send these captures to a server using the MQTT protocol. Arduino IDE, based on C ++, has been used to program the Wemos D1 Mini device.

It was calibrated and compared with the reference equipment [Brüel&Kjaer 2250 light](https://www.bksv.com/en/products/measuring-instruments/sound-level-meter/2250-series/Type-2250-L)

![](https://raw.githubusercontent.com/AGordiGuerrero/OpenSoundMeter/master/photos/comparacion02.png)

You can find the whole information of the project (in Spanish) at [Smart Open Lab](https://www.smartopenlab.com/proyecto/diseno-de-sonometro-de-medicion-continua-con-conectividad-wi-fi-basado-en-open-source/)
