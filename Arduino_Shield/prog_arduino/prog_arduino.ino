// encodeur

#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available

volatile unsigned int encoder0Pos = 0;

// Ammo led



// Bluetooth

#include <SoftwareSerial.h>
#define rxPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que RX, � raccorder sur TX du HC-05
#define baudrate 9600 
SoftwareSerial mySerial(rxPin ,txPin); //D�finition du software serial

// Transimp

int ADCpin 0



void setup() {

  // encodeur rotatoire

  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2

  Serial.begin (9600);
  Serial.println("start");                // a personal quirk

  // Bluetooth

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  mySerial.begin(baudrate);
  
} 


void loop() {

  // Relevé ADC
  
  int voltage_ADC = analogRead(ADCpin) / 4;


  // Bluetooth
  
  mySerial.write(voltage_ADC);

  // Encodeur

  /*
  Serial.print("Position:");
  Serial.println (encoder0Pos, DEC);  //Angle = (360 / Encoder_Resolution) * encoder0Pos
  */  

}

// Encodeur

/*
void doEncoder() {
  if (digitalRead(encoder0PinB)==HIGH) {
    encoder0Pos++;
  } else {
    encoder0Pos--;
  }
}
*/
