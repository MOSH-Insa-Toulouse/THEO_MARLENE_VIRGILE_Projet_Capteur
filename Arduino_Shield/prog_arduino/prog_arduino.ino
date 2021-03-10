  // encodeur

#define encoder0PinA  3  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 2 // Switch connection if available
volatile unsigned int encoder0Menu = 0;
volatile unsigned int Menu_State = 0 ;

  // Oled

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  // Bluetooth

#include <SoftwareSerial.h>
#define rxPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que RX, � raccorder sur TX du HC-05
#define baudrate 9600 
SoftwareSerial Serial_Phone(rxPin ,txPin); //D�finition du software serial

  // Transimp

int ADCpin 0

volatile unsigned int action_encoder = 0; // retient quelle action effectuer pour l'encodeur
volatile unsigned int temps_acquisition = 0;



void setup() {

  Serial.begin (9600);

  // encodeur rotatoire

  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(digitalPinToInterrupt(encoder0pinA), doEncoder, RISING); 
  attachInterrupt(digitalPinToInterrupt(Switch), doEncoderButton, RISING); 

  // Bluetooth

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  Serial_Phone.begin(baudrate);

  // Oled

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Setup ok !"));
  
} 



void loop() {

  // Encodeur et OLED -> affichage

  if (action_encoder == 0) {
  
    if (encoder0Menu == 0) {
      // affiche les actions possibles du menu choisi
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("MENU 1 : Relevé de résistance"));
    }
  
    else if (encoder0Menu == 1) {
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("MENU 2 : Définir temps d'acquisition"));
    }
  
    else if (encoder0Menu == 2) {
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("MENU 3 : Modifier le baudrate"));
    }
  
    else if (encoder0Menu == 3) {
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println(F("MENU 4 : "));
    }  

  }

  // Encodeur et OLED -> action
  if (Menu_State == 0) {
    // effectue les actions du menu choisi
    
      // Relevé ADC
    int voltage_ADC = analogRead(ADCpin) / 4;
      // Bluetooth
    mySerial.write(voltage_ADC);
    
  }
  
  else if (Menu_State == 1) {

    if (action_encodeur == 1) {

      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(WHITE);        // Draw white text
      display.setCursor(0,0);             // Start at top-left corner
      display.println("Temps d'acquisition : %d", temps_acquisition);
      
    }

    if (action_encodeur == 0) {

      mySerial.write(temps_acquisition);
    }
    
  }
  else if (Menu_State == 2) {

    
  }
  else if (Menu_State == 3) {
    

}



// Encodeur

// doEncoder increments or decrements the variable encoder0Menu that is used to set and chose actions, between 4 of them
void doEncoder() {

  if (action_encoder == 0) {
  
    if (digitalRead(encoder0PinB)==HIGH) {
      encoder0Menu = (encoder0Menu + 1) % 4;
    } 
    else {
      encoder0Menu = (encoder0Menu - 1) % 4;
    }

  }

  else if (action_encoder == 1) {

    if (digitalRead(encoder0PinB)==HIGH) {
      temps_acquisition = (encoder0Menu + 1) % 100;
    } 
    else {
      temps_acquisition = (encoder0Menu - 1) % 100;
    
  }
}

// doEncoderButton is activated when the button is clicked and affects a variable Menu_State with the encoder0Menu value
void doEncoderButton() {

  if (action_encoder == 0) {
    Menu_State = encoder0Menu

    if (encoder0Menu == 1) {
      action_encoder = 1 ;  
    }
  }

  if (action_encoder == 1) {
    action_encoder = 0
  }
  
}
