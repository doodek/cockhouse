EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Cockhouse Main Control Schematic"
Date ""
Rev "0A"
Comp "DogHouse Ltd."
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega8A-PU U?
U 1 1 6252F919
P 4250 3950
F 0 "U?" H 4250 5531 50  0000 C CNN
F 1 "ATmega8A-PU" H 4250 5440 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4250 3950 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Microchip%208bit%20mcu%20AVR%20ATmega8A%20data%20sheet%2040001974A.pdf" H 4250 3950 50  0001 C CNN
	1    4250 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3950 6200 3950
Wire Wire Line
	6200 3950 6200 5750
Wire Wire Line
	4850 4050 6100 4050
Wire Wire Line
	6100 4050 6100 5750
Text GLabel 6100 5750 3    50   BiDi ~ 0
I2C_clock
Text GLabel 6200 5750 3    50   BiDi ~ 0
I2C_data
Wire Wire Line
	4250 2550 4250 2500
Wire Wire Line
	4250 5350 4250 5400
Wire Wire Line
	4250 5400 4350 5400
$Comp
L Connector_Generic:Conn_01x05 J?
U 1 1 62537819
P 5700 5950
F 0 "J?" H 5780 5992 50  0000 L CNN
F 1 "ISP header" H 5780 5901 50  0000 L CNN
F 2 "" H 5700 5950 50  0001 C CNN
F 3 "~" H 5700 5950 50  0001 C CNN
	1    5700 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 2550 4350 2500
Connection ~ 4350 2500
Wire Wire Line
	4350 2500 4250 2500
Wire Wire Line
	4350 5350 4350 5400
Connection ~ 4350 5400
$Comp
L Device:R R?
U 1 1 62539431
P 3300 2700
F 0 "R?" H 3370 2746 50  0000 L CNN
F 1 "R" H 3370 2655 50  0000 L CNN
F 2 "" V 3230 2700 50  0001 C CNN
F 3 "~" H 3300 2700 50  0001 C CNN
	1    3300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2500 3300 2500
Wire Wire Line
	3300 2500 3300 2550
Connection ~ 4250 2500
Wire Wire Line
	3300 2850 3650 2850
$Comp
L Device:Crystal Y?
U 1 1 6253B701
P 3500 3150
F 0 "Y?" V 3454 3281 50  0000 L CNN
F 1 "Crystal" V 3545 3281 50  0000 L CNN
F 2 "" H 3500 3150 50  0001 C CNN
F 3 "~" H 3500 3150 50  0001 C CNN
	1    3500 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 3250 3650 3300
Wire Wire Line
	3650 3300 3500 3300
Wire Wire Line
	3500 3000 3650 3000
Wire Wire Line
	3650 3000 3650 3050
Wire Wire Line
	3300 2850 3300 3700
Connection ~ 3300 2850
$Comp
L Switch:SW_Push_Dual SW?
U 1 1 6253DD82
P 3300 3900
F 0 "SW?" V 3254 4048 50  0000 L CNN
F 1 "SW_Push_Dual" V 3345 4048 50  0000 L CNN
F 2 "" H 3300 4100 50  0001 C CNN
F 3 "~" H 3300 4100 50  0001 C CNN
	1    3300 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 4100 3300 5400
Wire Wire Line
	3300 5400 4250 5400
Connection ~ 4250 5400
Wire Wire Line
	4850 3150 5800 3150
Wire Wire Line
	5800 3150 5800 5750
Wire Wire Line
	4850 3250 5700 3250
Wire Wire Line
	5700 3250 5700 5750
Wire Wire Line
	4850 3350 5600 3350
Wire Wire Line
	5600 3350 5600 5750
Wire Wire Line
	5500 5400 5500 5750
Connection ~ 5500 5400
Wire Wire Line
	5500 5400 7000 5400
Wire Wire Line
	5900 5750 5900 2500
$Comp
L 74xx:74HC4051 U?
U 1 1 625302EB
P 7000 2950
F 0 "U?" H 7050 3631 50  0000 C CNN
F 1 "74HC4051" H 7050 3540 50  0000 C CNN
F 2 "" H 7000 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd74hc4051.pdf" H 7000 2550 50  0001 C CNN
	1    7000 2950
	1    0    0    -1  
$EndComp
Connection ~ 5900 2500
Wire Wire Line
	7000 2300 7000 2450
Wire Wire Line
	5900 2300 5900 2500
Wire Wire Line
	4850 2850 6700 2850
Wire Wire Line
	4850 2950 6700 2950
Wire Wire Line
	4850 3050 6700 3050
Wire Wire Line
	7000 3550 7000 3600
Wire Wire Line
	7100 3600 7100 3550
Wire Wire Line
	7100 3600 7000 3600
Connection ~ 7000 3600
Wire Wire Line
	7000 3600 7000 5400
Text Notes 8300 3700 2    50   ~ 0
Please see Vee in the datasheet.
Wire Wire Line
	7000 2300 8350 2300
Wire Wire Line
	8350 2300 8350 2650
Wire Wire Line
	8350 3350 8250 3350
Wire Wire Line
	8250 3250 8350 3250
Connection ~ 8350 3250
Wire Wire Line
	8350 3250 8350 3350
Wire Wire Line
	8250 3150 8350 3150
Connection ~ 8350 3150
Wire Wire Line
	8350 3150 8350 3250
Wire Wire Line
	8250 3050 8350 3050
Connection ~ 8350 3050
Wire Wire Line
	8350 3050 8350 3150
Wire Wire Line
	8250 2950 8350 2950
Connection ~ 8350 2950
Wire Wire Line
	8350 2950 8350 3050
Wire Wire Line
	8250 2850 8350 2850
Connection ~ 8350 2850
Wire Wire Line
	8350 2850 8350 2950
Wire Wire Line
	8250 2750 8350 2750
Connection ~ 8350 2750
Wire Wire Line
	8350 2750 8350 2850
Wire Wire Line
	8250 2650 8350 2650
Connection ~ 8350 2650
Wire Wire Line
	8350 2650 8350 2750
Wire Wire Line
	7650 3350 7400 3350
Wire Wire Line
	7400 3250 7650 3250
Wire Wire Line
	7650 3150 7400 3150
Wire Wire Line
	7400 3050 7650 3050
Wire Wire Line
	7650 2950 7400 2950
Wire Wire Line
	7400 2850 7650 2850
Wire Wire Line
	7650 2750 7400 2750
Wire Wire Line
	7400 2650 7650 2650
$Comp
L Switch:SW_DIP_x08 SW?
U 1 1 62562155
P 7950 3050
F 0 "SW?" H 7950 3717 50  0000 C CNN
F 1 "SW_DIP_x08" H 7950 3626 50  0000 C CNN
F 2 "" H 7950 3050 50  0001 C CNN
F 3 "~" H 7950 3050 50  0001 C CNN
	1    7950 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_DGS Q?
U 1 1 625682CA
P 6400 2400
F 0 "Q?" V 6743 2400 50  0000 C CNN
F 1 "Q_NMOS_DGS" V 6652 2400 50  0000 C CNN
F 2 "" H 6600 2500 50  0001 C CNN
F 3 "~" H 6400 2400 50  0001 C CNN
	1    6400 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5900 2300 6200 2300
Wire Wire Line
	6600 2300 7000 2300
Connection ~ 7000 2300
Wire Wire Line
	6400 2600 6400 3250
Wire Wire Line
	6400 3250 6700 3250
Wire Wire Line
	6400 3250 6400 4250
Wire Wire Line
	6400 4250 4850 4250
Connection ~ 6400 3250
Wire Wire Line
	6700 2650 6500 2650
Wire Wire Line
	6500 2650 6500 4350
Wire Wire Line
	6500 4350 4850 4350
Text Notes 6150 1950 0    50   ~ 0
Turn off Mux after read
Wire Wire Line
	4350 5400 4950 5400
Wire Wire Line
	4950 5400 4950 5800
Connection ~ 4950 5400
Wire Wire Line
	4950 5400 5200 5400
Text GLabel 4950 5800 3    50   BiDi ~ 0
GND
Wire Wire Line
	4350 2500 5900 2500
Text GLabel 5650 2300 0    50   BiDi ~ 0
+5V
Wire Wire Line
	5650 2300 5900 2300
Connection ~ 5900 2300
$Comp
L Switch:SW_SPDT SW?
U 1 1 625871D9
P 7800 4550
F 0 "SW?" H 7800 4835 50  0001 C CNN
F 1 "SW_SPDT" H 7800 4744 50  0001 C CNN
F 2 "" H 7800 4550 50  0001 C CNN
F 3 "~" H 7800 4550 50  0001 C CNN
	1    7800 4550
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 62588A23
P 7800 5050
F 0 "SW?" H 7800 5335 50  0001 C CNN
F 1 "SW_SPDT" H 7800 5244 50  0001 C CNN
F 2 "" H 7800 5050 50  0001 C CNN
F 3 "~" H 7800 5050 50  0001 C CNN
	1    7800 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4750 7450 4750
Wire Wire Line
	7600 4750 7600 4550
Wire Wire Line
	4850 4850 7450 4850
Wire Wire Line
	7600 4850 7600 5050
Text Notes 6250 4650 0    50   ~ 0
Limiting switches, top and bottom
$Comp
L Device:Q_NMOS_DGS Q?
U 1 1 625999DF
P 7850 5450
F 0 "Q?" V 8193 5450 50  0001 C CNN
F 1 "Q_NMOS_DGS" V 8102 5450 50  0001 C CNN
F 2 "" H 8050 5550 50  0001 C CNN
F 3 "~" H 7850 5450 50  0001 C CNN
	1    7850 5450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8200 4950 8000 4950
Wire Wire Line
	8200 4950 8200 5350
Connection ~ 8200 4950
Wire Wire Line
	8200 4950 8600 4950
Wire Wire Line
	7450 5350 7450 4850
Connection ~ 7450 4850
Wire Wire Line
	7450 4850 7600 4850
Wire Wire Line
	7650 4200 7450 4200
Wire Wire Line
	8050 4200 8200 4200
Wire Wire Line
	7450 4200 7450 4750
Connection ~ 7450 4750
Wire Wire Line
	7450 4750 7600 4750
Wire Wire Line
	8000 4450 8200 4450
Wire Wire Line
	8200 4450 8200 4200
Wire Wire Line
	8200 4450 8600 4450
Connection ~ 8200 4450
Wire Wire Line
	8050 5350 8200 5350
Wire Wire Line
	7450 5350 7650 5350
Wire Wire Line
	7850 3900 7200 3900
Wire Wire Line
	7200 3900 7200 4950
Wire Wire Line
	7200 5650 7850 5650
Wire Wire Line
	4850 4950 7200 4950
Connection ~ 7200 4950
Wire Wire Line
	7200 4950 7200 5650
$Comp
L Device:Q_NMOS_DGS Q?
U 1 1 625C5100
P 7850 4100
F 0 "Q?" V 8101 4100 50  0001 C CNN
F 1 "Q_NMOS_DGS" V 8192 4100 50  0001 C CNN
F 2 "" H 8050 4200 50  0001 C CNN
F 3 "~" H 7850 4100 50  0001 C CNN
	1    7850 4100
	0    -1   1    0   
$EndComp
Text GLabel 8600 4450 2    50   BiDi ~ 0
Motor_Forward
Text GLabel 8600 4950 2    50   BiDi ~ 0
Motor_Backwards
Text Notes 9450 4100 2    50   ~ 0
Override in case of mechanical failure
Text GLabel 5000 3550 2    50   BiDi ~ 0
Motor_Sense
Wire Wire Line
	5000 3550 4850 3550
Text GLabel 5000 3650 2    50   BiDi ~ 0
Temp_Sense
Wire Wire Line
	5000 3650 4850 3650
Wire Wire Line
	5200 4650 5200 5000
$Comp
L Device:R R?
U 1 1 625E34AB
P 5200 5150
F 0 "R?" H 5130 5104 50  0000 R CNN
F 1 "R" H 5130 5195 50  0000 R CNN
F 2 "" V 5130 5150 50  0001 C CNN
F 3 "~" H 5200 5150 50  0001 C CNN
	1    5200 5150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 5300 5200 5400
Connection ~ 5200 5400
Wire Wire Line
	5200 5400 5500 5400
$Comp
L Device:LED D?
U 1 1 625EFE59
P 5050 4650
F 0 "D?" H 5043 4395 50  0000 C CNN
F 1 "LED" H 5043 4486 50  0000 C CNN
F 2 "" H 5050 4650 50  0001 C CNN
F 3 "~" H 5050 4650 50  0001 C CNN
	1    5050 4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 4650 4850 4650
$EndSCHEMATC
