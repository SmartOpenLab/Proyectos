EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ESP-RFID Lock Control"
Date "2019-02-13"
Rev "V0.1"
Comp "Smart Open Lab"
Comment1 "Based on ESP-RFID Project: https://github.com/esprfid"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CerraduraESP_RFID_V1.0-rescue:WeMos_mini-wemos-CerraduraESP_RFID_V01-rescue U3
U 1 1 5C6324F6
P 5900 2900
F 0 "U3" H 5900 3800 60  0000 C CNN
F 1 "WeMos_mini" H 5900 3700 60  0000 C CNN
F 2 "wemos-d1-mini:wemos-d1-mini-with-pin-header-and-connector" H 6450 2200 60  0001 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 5900 3600 60  0000 C CNN
F 4 "A mini wifi board with 4MB flash based on ESP-8266EX." H 5900 2900 50  0001 C CNN "Description"
F 5 "WEMOS Electronics" H 5900 2900 50  0001 C CNN "MFN"
F 6 "Wemos D1 Mini" H 5900 2900 50  0001 C CNN "MFP"
F 7 "Banggood" H 5900 2900 50  0001 C CNN "Source1"
F 8 "https://www.banggood.com/WeMos-D1-mini-V2_2_0-WIFI-Internet-Development-Board-Based-ESP8266-4MB-FLASH-ESP-12S-Chip-p-1143874.html?rmmds=buy&cur_warehouse=CN" H 5900 2900 50  0001 C CNN "Source1Link"
F 9 "2.99€" H 5900 2900 50  0001 C CNN "Source1Price"
	1    5900 2900
	1    0    0    -1  
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:OLED_I2C_128x64--CerraduraESP_RFID_V01-rescue U1
U 1 1 5C474880
P 4400 3200
F 0 "U1" H 4256 2792 60  0000 C CNN
F 1 "I2C_4x4_keyboard" H 4264 2892 60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x04_Pitch2.54mm" H 4750 3150 60  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/pcf8574.pdf" H 4750 3150 60  0001 C CNN
F 4 "PCF8574 IO Board PCF8574T Module Extension Module I/O Extension Module I2C I / O" H 4400 3200 50  0001 C CNN "Characteristics"
F 5 "Ebay" H 4400 3200 50  0001 C CNN "Source1"
F 6 "https://www.ebay.com/itm/PCF8574-IO-Board-PCF8574T-Module-Extension-Module-I-O-Extension-Module-I2C-I-O/202596641612?hash=item2f2bb36b4c:g:nxoAAOSwRYNcZMrm" H 4400 3200 50  0001 C CNN "Source1Link"
F 7 "0.99 €" H 4400 3200 50  0001 C CNN "Source1Price"
	1    4400 3200
	1    0    0    1   
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:C--CerraduraESP_RFID_V01-rescue C3
U 1 1 5C474883
P 5800 5000
F 0 "C3" H 5924 5065 50  0000 L CNN
F 1 "100n" H 5924 4982 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 5838 4850 50  0001 C CNN
F 3 "" H 5800 5000 50  0000 C CNN
	1    5800 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female P1
U 1 1 5C47488B
P 2800 4850
F 0 "P1" H 2792 4510 50  0000 C CNN
F 1 "CONN_01X03" H 2856 4620 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-3_P5.08mm" H 2800 4850 50  0001 C CNN
F 3 "" H 2800 4850 50  0000 C CNN
F 4 "5.08 mm pitch. 3 terminal" H 2800 4850 50  0001 C CNN "Characteristics"
F 5 "Fixed Terminal Block Connector. Screw, PCB through Hole " H 2800 4850 50  0001 C CNN "Description"
F 6 "BC-508X10" H 2800 4850 50  0001 C CNN "Package ID"
F 7 "Phoenix Contact" H 2800 4850 50  0001 C CNN "MFN"
F 8 "5442219" H 2800 4850 50  0001 C CNN "MFP"
F 9 "Mouser" H 2800 4850 50  0001 C CNN "Source1"
F 10 "651-5442219" H 2800 4850 50  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/Phoenix-Contact/5442219?qs=sGAEpiMZZMvZTcaMAxB2AHWjwpGN5e0jS1xvnyQpmZg%3D" H 2800 4850 50  0001 C CNN "Source1Link"
F 12 "1.34 €" H 2800 4850 50  0001 C CNN "Source1Price"
	1    2800 4850
	-1   0    0    1   
$EndComp
Text Notes 4450 4200 2    60   ~ 0
Power Supply
Text GLabel 5800 4650 1    60   Input ~ 0
+5V
Wire Wire Line
	5800 4650 5800 4750
Wire Wire Line
	5350 5150 5350 5050
Connection ~ 5350 5150
Connection ~ 5800 4750
Wire Wire Line
	5750 4750 5800 4750
$Comp
L CerraduraESP_RFID_V1.0-rescue:D_Bridge_+-AA--CerraduraESP_RFID_V01-rescue D2
U 1 1 5C474A43
P 3750 4750
F 0 "D2" H 3706 5216 50  0000 L CNN
F 1 "D_Bridge_+-AA" H 3468 5142 50  0000 L CNN
F 2 "Diodes_THT:Diode_Bridge_Round_D8.9mm" H 3750 4750 50  0001 C CNN
F 3 "" H 3750 4750 50  0001 C CNN
	1    3750 4750
	1    0    0    1   
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:CONN_01X02--CerraduraESP_RFID_V01-rescue P3
U 1 1 5C474BB3
P 8200 4300
F 0 "P3" H 8200 4450 50  0000 C CNN
F 1 "CONN_01X02" V 8300 4300 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 8200 4300 50  0001 C CNN
F 3 "" H 8200 4300 50  0000 C CNN
F 4 "5.08 mm pitch. 2 terminal" H 2800 4850 50  0001 C CNN "Characteristics"
F 5 "Fixed Terminal Block Connector. Screw, pluggable, PCB through Hole " H 2800 4850 50  0001 C CNN "Description"
F 6 "MSTB" H 2800 4850 50  0001 C CNN "Package ID"
F 7 "Phoenix Contact" H 2800 4850 50  0001 C CNN "MFN"
F 8 "1758856" H 2800 4850 50  0001 C CNN "MFP"
F 9 "Mouser" H 2800 4850 50  0001 C CNN "Source1"
F 10 "651-1758856" H 2800 4850 50  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/Phoenix-Contact/1758856?qs=sGAEpiMZZMsDddcp1dBDJOrXMrFmZFLlqGk%2FSTtpbpg%3D" H 2800 4850 50  0001 C CNN "Source1Link"
F 12 "1.67 €" H 2800 4850 50  0001 C CNN "Source1Price"
	1    8200 4300
	1    0    0    -1  
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:GND--CerraduraESP_RFID_V01-rescue #PWR04
U 1 1 5C474DA8
P 5350 5150
F 0 "#PWR04" H 5350 4900 50  0001 C CNN
F 1 "GND" H 5350 5000 50  0000 C CNN
F 2 "" H 5350 5150 50  0000 C CNN
F 3 "" H 5350 5150 50  0000 C CNN
	1    5350 5150
	1    0    0    -1  
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:PWR_FLAG--CerraduraESP_RFID_V01-rescue #FLG01
U 1 1 5C474E6E
P 4900 5150
F 0 "#FLG01" H 4900 5245 50  0001 C CNN
F 1 "PWR_FLAG" H 4900 5330 50  0000 C CNN
F 2 "" H 4900 5150 50  0000 C CNN
F 3 "" H 4900 5150 50  0000 C CNN
	1    4900 5150
	-1   0    0    1   
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:R--CerraduraESP_RFID_V01-rescue R1
U 1 1 5C479854
P 4550 5000
F 0 "R1" H 4442 5048 50  0000 C CNN
F 1 "220k" H 4402 4952 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4480 5000 50  0001 C CNN
F 3 "" H 4550 5000 50  0000 C CNN
F 4 "2W, 500V" H 4550 5000 60  0001 C CNN "Characteristics"
F 5 "Metal film through hole resistor" H 4550 5000 60  0001 C CNN "Description"
F 6 "FMP" H 4550 5000 60  0001 C CNN "Package ID"
F 7 "Yageo" H 4550 5000 60  0001 C CNN "MFN"
F 8 "FMP200JR-52-220K" H 4550 5000 60  0001 C CNN "MFP"
F 9 "Mouser" H 4550 5000 60  0001 C CNN "Source1"
F 10 "603-FMP200JR-52-220K" H 4550 5000 60  0001 C CNN "Source1Part"
F 11 "http://www.mouser.es/ProductDetail/Yageo/FMP200JR-52-220K/?qs=sGAEpiMZZMu61qfTUdNhGztMfEiwFKKT8tJfn5xrilY%3d" H 4550 5000 60  0001 C CNN "Source1Link"
F 12 "Value" H 4550 5000 60  0001 C CNN "Notes"
F 13 "0.245€" H 4550 5000 60  0001 C CNN "Source1Price"
	1    4550 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5150 5800 5150
Wire Wire Line
	5800 4750 5800 4850
Wire Wire Line
	4550 4750 4550 4850
Wire Wire Line
	4550 5150 4900 5150
Wire Wire Line
	3000 4950 3100 4950
Wire Wire Line
	3450 4950 3450 4750
Wire Wire Line
	3000 4750 3000 4450
Wire Wire Line
	3000 4450 3750 4450
Wire Wire Line
	3000 4850 3150 4850
Wire Wire Line
	3150 4850 3150 5050
Wire Wire Line
	3150 5050 3750 5050
Wire Wire Line
	3100 4950 3100 5150
Connection ~ 3100 4950
Wire Wire Line
	3100 4950 3450 4950
Connection ~ 4550 4750
Connection ~ 4900 5150
$Comp
L CerraduraESP_RFID_V1.0-rescue:RFID-RC522-MODULE-rfid-rc522-module-CerraduraESP_RFID_V01-rescue P2
U 1 1 5C62C7C2
P 7700 2950
F 0 "P2" V 6832 2935 60  0000 L CNN
F 1 "RFID-RC522-MODULE" V 6958 2557 60  0000 L CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x08_Pitch2.54mm" H 7700 2950 60  0001 C CNN
F 3 "" H 7700 2950 60  0000 C CNN
F 4 "3.3V RC522 Chip IC Card Induction Module RFID Reader 13.56MHz 10Mbit/s" H 7700 2950 50  0001 C CNN "Description"
F 5 "Banggood" H 7700 2950 50  0001 C CNN "Source1"
F 6 "https://www.banggood.com/RC522-Chip-IC-Card-Induction-Module-RFID-Reader-p-81067.html?rmmds=search&cur_warehouse=CN" H 7700 2950 50  0001 C CNN "Source1Link"
F 7 "Supported card types: mifare1 S50, mifare1 S70 MIFARE Ultralight, mifare Pro, MIFARE DESFire" H 7700 2950 50  0001 C CNN "Notes"
F 8 "2.69 €" H 7700 2950 50  0001 C CNN "Source1Price"
	1    7700 2950
	0    1    1    0   
$EndComp
Text GLabel 4550 4650 1    60   Input ~ 0
+VDC
Wire Wire Line
	4550 4650 4550 4750
Text GLabel 4850 3250 2    60   Input ~ 0
+5V
Wire Wire Line
	4700 3250 4850 3250
Text GLabel 5350 2550 1    60   Input ~ 0
+5V
$Comp
L CerraduraESP_RFID_V1.0-rescue:GND--CerraduraESP_RFID_V01-rescue #PWR02
U 1 1 5C6301AB
P 4800 3350
F 0 "#PWR02" H 4800 3100 50  0001 C CNN
F 1 "GND" H 4800 3200 50  0000 C CNN
F 2 "" H 4800 3350 50  0000 C CNN
F 3 "" H 4800 3350 50  0000 C CNN
	1    4800 3350
	1    0    0    -1  
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:GND--CerraduraESP_RFID_V01-rescue #PWR03
U 1 1 5C6301D4
P 5200 2600
F 0 "#PWR03" H 5200 2350 50  0001 C CNN
F 1 "GND" H 5200 2450 50  0000 C CNN
F 2 "" H 5200 2600 50  0000 C CNN
F 3 "" H 5200 2600 50  0000 C CNN
	1    5200 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4800 3350 4700 3350
Text GLabel 6500 2550 2    60   Input ~ 0
+3.3V
Wire Wire Line
	6400 2550 6500 2550
Wire Wire Line
	6400 2850 7150 2850
Wire Wire Line
	6400 2950 7000 2950
Wire Wire Line
	7000 2950 7000 2550
Wire Wire Line
	7000 2550 7150 2550
Wire Wire Line
	7150 2400 6900 2400
Wire Wire Line
	6900 2400 6900 2650
Wire Wire Line
	6900 2650 6400 2650
Wire Wire Line
	6400 2750 7150 2750
Wire Wire Line
	7150 2750 7150 2700
Text GLabel 7050 3450 0    60   Input ~ 0
+3.3V
$Comp
L CerraduraESP_RFID_V1.0-rescue:GND--CerraduraESP_RFID_V01-rescue #PWR05
U 1 1 5C638775
P 6950 3150
F 0 "#PWR05" H 6950 2900 50  0001 C CNN
F 1 "GND" H 6950 3000 50  0000 C CNN
F 2 "" H 6950 3150 50  0000 C CNN
F 3 "" H 6950 3150 50  0000 C CNN
	1    6950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 3150 7150 3150
Wire Wire Line
	7050 3450 7150 3450
NoConn ~ 7150 3000
NoConn ~ 7150 3300
Wire Wire Line
	4700 3150 4850 3150
Wire Wire Line
	4850 3150 4850 2950
Wire Wire Line
	4850 2950 5400 2950
Wire Wire Line
	4700 3050 5400 3050
$Comp
L LED:SK6812 D1
U 1 1 5C647276
P 3750 2500
F 0 "D1" H 3576 2832 50  0000 R CNN
F 1 "NeoPixel_THT" H 3714 2756 50  0000 R CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 3800 2200 50  0001 L TNN
F 3 "https://www.adafruit.com/product/1938" H 3850 2125 50  0001 L TNN
F 4 "Digital RGB LED" H 3750 2500 50  0001 C CNN "Characteristics"
F 5 "Adafruit NeoPixel Digital RGB LED Strip - White 30 LED - WHITE" H 3750 2500 50  0001 C CNN "Description"
F 6 "Adafruit" H 3750 2500 50  0001 C CNN "MFN"
F 7 "Adafruit" H 3750 2500 50  0001 C CNN "Source1"
F 8 "https://www.adafruit.com/product/1376?length=1" H 3750 2500 50  0001 C CNN "Source1Link"
F 9 "16.95 €" H 3750 2500 50  0001 C CNN "Source1Price"
	1    3750 2500
	-1   0    0    -1  
$EndComp
Text GLabel 3750 2100 1    60   Input ~ 0
+5V
$Comp
L CerraduraESP_RFID_V1.0-rescue:GND--CerraduraESP_RFID_V01-rescue #PWR01
U 1 1 5C64F2AD
P 3750 2850
F 0 "#PWR01" H 3750 2600 50  0001 C CNN
F 1 "GND" H 3750 2700 50  0000 C CNN
F 2 "" H 3750 2850 50  0000 C CNN
F 3 "" H 3750 2850 50  0000 C CNN
	1    3750 2850
	1    0    0    -1  
$EndComp
NoConn ~ 3450 2500
NoConn ~ 5400 3150
NoConn ~ 5400 3250
NoConn ~ 6400 3250
NoConn ~ 6400 3150
$Comp
L Device:Q_NPN_CBE Q1
U 1 1 5C65A784
P 7200 4900
F 0 "Q1" H 7391 4946 50  0000 L CNN
F 1 "2N3904" H 7391 4855 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 7400 5000 50  0001 C CNN
F 3 "~" H 7200 4900 50  0001 C CNN
F 4 "BJT 200mA 60V 300MHz NPN" H 7200 4900 50  0001 C CNN "Characteristics"
F 5 "Bipolar Transistor" H 7200 4900 50  0001 C CNN "Description"
F 6 "TO-92-3" H 7200 4900 50  0001 C CNN "Package ID"
F 7 "ON Semiconductor" H 7200 4900 50  0001 C CNN "MFN"
F 8 "2N3904BU" H 7200 4900 50  0001 C CNN "MFP"
F 9 "Mouser" H 7200 4900 50  0001 C CNN "Source1"
F 10 "512-2N3904BU" H 7200 4900 50  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/ON-Semiconductor/2N3904?qs=sGAEpiMZZMshyDBzk1%2FWi%2FPUgtclNldlwKyt3DLKFPI%3D" H 7200 4900 50  0001 C CNN "Source1Link"
F 12 "0.183 €" H 7200 4900 50  0001 C CNN "Source1Price"
	1    7200 4900
	1    0    0    -1  
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:R--CerraduraESP_RFID_V01-rescue R2
U 1 1 5C65A9C8
P 6800 4900
F 0 "R2" H 6923 4960 50  0000 C CNN
F 1 "10k" H 6917 4876 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6730 4900 50  0001 C CNN
F 3 "https://www.mouser.es/datasheet/2/447/Yageo%20LR_MFR_2013-467719.pdf" H 6800 4900 50  0001 C CNN
F 4 "1/4W 1% " H 6800 4900 60  0001 C CNN "Characteristics"
F 5 "Metal film through hole resistor" H 6800 4900 60  0001 C CNN "Description"
F 6 "FMR-25" H 6800 4900 60  0001 C CNN "Package ID"
F 7 "Yageo" H 6800 4900 60  0001 C CNN "MFN"
F 8 "MFR-25FRF5210K" H 6800 4900 60  0001 C CNN "MFP"
F 9 "Mouser" H 6800 4900 60  0001 C CNN "Source1"
F 10 "603-MFR-25FRF5210K" H 6800 4900 60  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/Yageo/MFR-25FRF52-10K?qs=sGAEpiMZZMu61qfTUdNhGztMfEiwFKKTpKeEBKehEYg%3D" H 6800 4900 60  0001 C CNN "Source1Link"
F 12 "Value" H 6800 4900 60  0001 C CNN "Notes"
F 13 "0.245€" H 6800 4900 60  0001 C CNN "Source1Price"
	1    6800 4900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3750 2100 3750 2200
Wire Wire Line
	3750 2800 3750 2850
Wire Wire Line
	6950 4900 7000 4900
$Comp
L Device:Q_NMOS_GDS Q2
U 1 1 5C63EA64
P 7900 4700
F 0 "Q2" H 8106 4746 50  0000 L CNN
F 1 "BUZ31" H 8106 4655 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 8100 4800 50  0001 C CNN
F 3 "~" H 7900 4700 50  0001 C CNN
F 4 "200V 14.5A 0.2Ω" H 7900 4700 50  0001 C CNN "Characteristics"
F 5 "SIPMOS Power Transistor N channel• Enhancement mode• Avalanche-rated " H 7900 4700 50  0001 C CNN "Description"
F 6 "TO-220 " H 7900 4700 50  0001 C CNN "Package ID"
F 7 "Siemens" H 7900 4700 50  0001 C CNN "MFN"
F 8 "ABC67078-S.1304-A2" H 7900 4700 50  0001 C CNN "MFP"
F 9 "Obsolete. Can be replaced by other newer MOSFET." H 7900 4700 50  0001 C CNN "Notes"
	1    7900 4700
	1    0    0    -1  
$EndComp
$Comp
L CerraduraESP_RFID_V1.0-rescue:GND--CerraduraESP_RFID_V01-rescue #PWR06
U 1 1 5C63EC44
P 7700 5300
F 0 "#PWR06" H 7700 5050 50  0001 C CNN
F 1 "GND" H 7700 5150 50  0000 C CNN
F 2 "" H 7700 5300 50  0000 C CNN
F 3 "" H 7700 5300 50  0000 C CNN
	1    7700 5300
	1    0    0    -1  
$EndComp
Text GLabel 8000 4050 1    60   Input ~ 0
+VDC
Wire Wire Line
	8000 4050 8000 4100
Wire Wire Line
	8000 5300 7700 5300
Wire Wire Line
	7300 5300 7300 5100
Wire Wire Line
	8000 4900 8000 5300
Connection ~ 7700 5300
Wire Wire Line
	7700 5300 7300 5300
Wire Wire Line
	7300 4700 7700 4700
Connection ~ 7300 4700
Text GLabel 7300 4000 1    60   Input ~ 0
+5V
Wire Wire Line
	8000 4350 8000 4400
Wire Wire Line
	7300 4000 7300 4200
Wire Wire Line
	7300 4500 7300 4700
Wire Wire Line
	6550 3050 6550 4900
Wire Wire Line
	6550 4900 6650 4900
Wire Wire Line
	6400 3050 6550 3050
Wire Wire Line
	5400 2850 4700 2850
Wire Wire Line
	4700 2850 4700 2500
Wire Wire Line
	4700 2500 4050 2500
Wire Wire Line
	4950 4750 4950 4850
$Comp
L CerraduraESP_RFID_V1.0-rescue:LM7812-RESCUE-SmartScarecrow_V0.4--CerraduraESP_RFID_V01-rescue U2
U 1 1 5C47487F
P 5350 4800
F 0 "U2" H 5346 5079 50  0000 C CNN
F 1 "LM7805" H 5350 5000 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 5350 4800 50  0001 C CNN
F 3 "http://www.ti.com/general/docs/suppproductinfo.tsp?distId=26&gotoUrl=https%3A%2F%2Fwww.ti.com%2Flit%2Fds%2Fsymlink%2Flm340.pdf" H 5350 4800 50  0001 C CNN
F 4 "5V, 1A, Min 7.5V, Max. 35V" H 5350 4800 50  0001 C CNN "Characteristics"
F 5 "Linear Voltage Regulator" H 5350 4800 50  0001 C CNN "Description"
F 6 "TO-220" H 5350 4800 50  0001 C CNN "Package ID"
F 7 "Texas Instruments" H 5350 4800 50  0001 C CNN "MFN"
F 8 "LM7805CT " H 5350 4800 50  0001 C CNN "MFP"
F 9 "Mouser" H 5350 4800 50  0001 C CNN "Source1"
F 10 "926-LM7805CT" H 5350 4800 50  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/Texas-Instruments/LM7805CT?qs=sGAEpiMZZMtUqDgmOWBjgJwP%252B5MP6LxOR0ypFNmpAFU%3D" H 5350 4800 50  0001 C CNN "Source1Link"
F 12 "1.48 €" H 5350 4800 50  0001 C CNN "Source1Price"
	1    5350 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4750 4950 4750
Wire Wire Line
	4950 5150 5350 5150
Wire Wire Line
	4900 5150 4950 5150
Connection ~ 4950 5150
$Comp
L CerraduraESP_RFID_V1.0-rescue:C--CerraduraESP_RFID_V01-rescue C2
U 1 1 5C474891
P 4950 5000
F 0 "C2" H 4734 5050 50  0000 L CNN
F 1 "330n" H 4667 4955 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 4988 4850 50  0001 C CNN
F 3 "" H 4950 5000 50  0000 C CNN
	1    4950 5000
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D3
U 1 1 5C66AF77
P 7750 4250
F 0 "D3" V 7550 4100 50  0000 L CNN
F 1 "1N4007" V 7650 3950 50  0000 L CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P7.62mm_Horizontal" H 7750 4075 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 7750 4250 50  0001 C CNN
F 4 "1000V, 1A" H 7750 4250 50  0001 C CNN "Characteristics"
F 5 "Standard Recovery Rectifier Diode" H 7750 4250 50  0001 C CNN "Description"
F 6 "DO-41" H 7750 4250 50  0001 C CNN "Package ID"
F 7 "Vishay Semiconductors" H 7750 4250 50  0001 C CNN "MFN"
F 8 "1N4007E-E3/53 " H 7750 4250 50  0001 C CNN "MFP"
F 9 "Mouser" H 7750 4250 50  0001 C CNN "Source1"
F 10 "625-1N4007E-E3/53" H 7750 4250 50  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/Vishay-Semiconductors/1N4007E-E3-53?qs=sGAEpiMZZMvplms98TlKY6I1zmttAFjhccvxj7xVmAE%3D" H 7750 4250 50  0001 C CNN "Source1Link"
F 12 "0.42€" H 7750 4250 50  0001 C CNN "Source1Price"
	1    7750 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 4100 8000 4100
Connection ~ 8000 4100
Wire Wire Line
	8000 4100 8000 4250
Wire Wire Line
	7750 4400 8000 4400
Connection ~ 8000 4400
Wire Wire Line
	8000 4400 8000 4500
$Comp
L CerraduraESP_RFID_V1.0-rescue:C--CerraduraESP_RFID_V01-rescue C1
U 1 1 5C825A0F
P 4250 4950
F 0 "C1" H 4034 5000 50  0000 L CNN
F 1 "100u" H 3967 4905 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P3.80mm" H 4288 4800 50  0001 C CNN
F 3 "" H 4250 4950 50  0000 C CNN
	1    4250 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 4750 4250 4750
Wire Wire Line
	4250 4750 4250 4800
Connection ~ 4250 4750
Wire Wire Line
	4250 4750 4550 4750
Wire Wire Line
	3100 5150 4250 5150
Connection ~ 4550 5150
Wire Wire Line
	4250 5100 4250 5150
Connection ~ 4250 5150
Wire Wire Line
	4250 5150 4550 5150
$Comp
L CerraduraESP_RFID_V1.0-rescue:R--CerraduraESP_RFID_V01-rescue R3
U 1 1 5C8329F3
P 7300 4350
F 0 "R3" H 7423 4410 50  0000 C CNN
F 1 "10k" H 7417 4326 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7230 4350 50  0001 C CNN
F 3 "https://www.mouser.es/datasheet/2/447/Yageo%20LR_MFR_2013-467719.pdf" H 7300 4350 50  0001 C CNN
F 4 "1/4W 1% " H 7300 4350 60  0001 C CNN "Characteristics"
F 5 "Metal film through hole resistor" H 7300 4350 60  0001 C CNN "Description"
F 6 "FMR-25" H 7300 4350 60  0001 C CNN "Package ID"
F 7 "Yageo" H 7300 4350 60  0001 C CNN "MFN"
F 8 "MFR-25FRF5210K" H 7300 4350 60  0001 C CNN "MFP"
F 9 "Mouser" H 7300 4350 60  0001 C CNN "Source1"
F 10 "603-MFR-25FRF5210K" H 7300 4350 60  0001 C CNN "Source1Part"
F 11 "https://www.mouser.es/ProductDetail/Yageo/MFR-25FRF52-10K?qs=sGAEpiMZZMu61qfTUdNhGztMfEiwFKKTpKeEBKehEYg%3D" H 7300 4350 60  0001 C CNN "Source1Link"
F 12 "Value" H 7300 4350 60  0001 C CNN "Notes"
F 13 "0.245€" H 7300 4350 60  0001 C CNN "Source1Price"
	1    7300 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 5C840B31
P 4950 2650
F 0 "BZ1" H 4956 2325 50  0000 C CNN
F 1 "Buzzer" H 4956 2416 50  0000 C CNN
F 2 "Buzzers_Beepers:Buzzer_12x9.5RM7.6" V 4925 2750 50  0001 C CNN
F 3 "~" V 4925 2750 50  0001 C CNN
	1    4950 2650
	-1   0    0    1   
$EndComp
Wire Wire Line
	5350 2550 5400 2550
Wire Wire Line
	5050 2550 5050 2650
Wire Wire Line
	5050 2650 5200 2650
Wire Wire Line
	5200 2600 5200 2650
Connection ~ 5200 2650
Wire Wire Line
	5200 2650 5400 2650
Wire Wire Line
	5050 2750 5400 2750
$EndSCHEMATC
