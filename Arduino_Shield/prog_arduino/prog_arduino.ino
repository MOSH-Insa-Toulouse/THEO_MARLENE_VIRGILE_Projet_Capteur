  // Rotary Encoder

#define encoder0PinA  3  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 2 // Switch connection if available
volatile unsigned int encoder0Menu_temp = 0;
volatile unsigned int encoder0Menu = 0;
volatile unsigned int Menu_State = 0 ;

volatile unsigned int action_encoder = 0; // retient quelle action effectuer pour l'encodeur
volatile unsigned int temps_acquisition_temp = 0;
volatile unsigned int temps_acquisition = 0;

int temps_choisi = 0;

int State;
int Old_State;

  // Oled 

  // if any problem occurs make Ctrl+Maj+i and add Adafruit_BusIO_Register , Adafruit_SSD1306 , Adafruit_GFX

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  // Bluetooth

#include <SoftwareSerial.h>
#define rxPin 10 //Broche 10 en tant que RX, � raccorder sur TX du HC-05
#define txPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define baudrate 9600 
SoftwareSerial Serial_Phone(rxPin ,txPin); //D�finition du software serial

  // Transimp

#define ADCpin  0

  // Global variables 

int resistance = 0;
float tension;
int R1 = 100;
int R2 = 1;
int R3 = 100;
int R5 = 10;
int voltage_ADC;


  // Fonctions Encodeur

// doEncoder increments or decrements the variable encoder0Menu that is used to navigate into menues, between 4 of them, also used to increments the "temps_acquisition" variable
void doEncoder() {

  State = digitalRead(encoder0PinA);

  if (action_encoder == 0) {
  
    if (State != Old_State)
    {
      if (digitalRead(encoder0PinB) != State)
      {
        encoder0Menu_temp = (encoder0Menu_temp + 1) % 8;
        encoder0Menu = encoder0Menu_temp/2;
      }
      else {
        encoder0Menu_temp = (encoder0Menu_temp - 1) % 8;
        encoder0Menu = encoder0Menu_temp/2;
      }
    }

  }

  else if ((action_encoder == 1) and (temps_choisi == 0) and (Menu_State == 2)) {

    if (State != Old_State)
    {
      if (digitalRead(encoder0PinB) != State)
      {
        temps_acquisition_temp = (temps_acquisition_temp + 1) % 60;
        temps_acquisition = temps_acquisition_temp / 2;
      }
      else {
        temps_acquisition_temp = (temps_acquisition_temp - 1) % 60;
        temps_acquisition = temps_acquisition_temp / 2;
      }
    }
    
  }
}


// doEncoderButton is activated when the button is clicked and affects a variable Menu_State with the encoder0Menu value, also checks if the time is chosen when the third menu is activated
void doEncoderButton() {

  if (action_encoder == 0) {
    Menu_State = encoder0Menu ;
    action_encoder = 1 ;
    }

  else if ((action_encoder == 1) and (Menu_State == 2)) {

    if (temps_choisi == 0) {
      temps_choisi = 1;
    }

    else if (temps_choisi == 1) {
      action_encoder = 0 ;
      temps_choisi = 0;
    }
  }

  else if (action_encoder == 1) {
    action_encoder = 0 ;
  }

  delay(200);
}

  // Fonctions de simplification

void setup_display() {

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  
}


void setup() {

  Serial.begin(9600);

  // encodeur rotatoire

  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  pinMode(Switch, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(3), doEncoder, RISING); 
  attachInterrupt(digitalPinToInterrupt(2), doEncoderButton, FALLING); 


  // Bluetooth

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  Serial_Phone.begin(baudrate);

  // Oled

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  
} 



void loop() {

  // Encodeur et OLED -> affichage

  if (action_encoder == 0) {
  
    if (encoder0Menu == 0) {
      // affiche les actions possibles du menu choisi
      setup_display();
      display.println(F("MENU 1 : \nReleve de resistance"));
      display.display();
    }
  
    else if (encoder0Menu == 1) {
      setup_display();
      display.println(F("MENU 2 : \nReleve de tension"));
      display.display();
    }
  
    else if (encoder0Menu == 2) {
      setup_display();
      display.println(F("MENU 3 : \nDefinir le temps \nd'aquisition"));
      display.display();
    }
  
    else if (encoder0Menu == 3) {
      setup_display();
      display.println(F("MENU 4 : "));
      display.display();
    }  

  }

  // Encodeur et OLED -> action
  
  else if (action_encoder == 1) {
 
    if (Menu_State == 0) {
    
        // Relevé ADC
      voltage_ADC = analogRead(ADCpin) / 4;
        // Bluetooth
      Serial_Phone.write(voltage_ADC);
      delay(500);
      Serial.print(voltage_ADC + String(" "));
      Serial.println(millis());

      resistance = (R1 * (1 + (R3/R2)) * (5 / (voltage_ADC*0.01952)) - R1 - R5) / 1000;

      setup_display();
      display.println("Resistance : ");
      if (resistance != 0) {
        display.print(resistance);
        display.println(" MOhm  - Envoi BT");
      }
      else {
        display.print("Infini");
        display.println("   - Envoi BT");
      }
      display.println("\n        Press to quit");
      display.display();
      
    
    }
  
    else if (Menu_State == 1) {

        // Relevé ADC
      voltage_ADC = analogRead(ADCpin) / 4;
        // Bluetooth
      Serial_Phone.write(voltage_ADC);

      tension = voltage_ADC * 0.01952;
      
      setup_display();
      display.println("Tension : ");
      display.print(tension);
      display.println(" V   - Envoi BT");
      display.println("\n        Press to quit");
      display.display();
      
    }

    else if (Menu_State == 2) {

      if (temps_choisi == 0) {

        setup_display();
        display.println("Temps d'acquisition :");
        display.print(temps_acquisition);
        display.println(" s");
        display.println("\n       Press to chose");
        display.display();

      }

      else if (temps_choisi == 1) {

        setup_display();
        display.println("Temps d'acquisition :");
        display.print(temps_acquisition);
        display.println(" s   - Envoi BT");
        display.println("\n        Press to quit");
        display.display();

        Serial_Phone.write(temps_acquisition);

      }
    
    }
    else if (Menu_State == 3) {
    
      setup_display();
      display.println("Pas de menu");
      display.println("");
      display.println("\n        Press to quit");
      display.display();

    }

  }

}
