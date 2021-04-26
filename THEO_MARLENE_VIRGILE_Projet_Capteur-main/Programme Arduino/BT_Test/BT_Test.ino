// Bluetooth

#include <SoftwareSerial.h>
#define rxPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que RX, � raccorder sur TX du HC-05
#define baudrate 9600 
SoftwareSerial Serial_Phone(rxPin ,txPin); //D�finition du software serial

  // Transimp

#define ADCpin  0


void setup() {

  Serial.begin (9600);

  // Bluetooth

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  Serial_Phone.begin(baudrate);  

}



void loop() {

    // Relevé ADC
  int voltage_ADC = analogRead(ADCpin) / 4;
    // Bluetooth
  Serial_Phone.write(voltage_ADC);
  Serial.print(voltage_ADC);

}


// BT test OK !
