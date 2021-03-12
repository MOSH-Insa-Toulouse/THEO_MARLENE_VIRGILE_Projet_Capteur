// encoder

#define encoder0PinA  3  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 2 // Switch connection if available
volatile unsigned int encoder0Menu = 0;
volatile unsigned int Menu_State = 0 ;

volatile unsigned int action_encoder = 0; // retient quelle action effectuer pour l'encodeur
volatile unsigned int temps_acquisition = 0;

  // Fonctions Encodeur

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
}

// doEncoderButton is activated when the button is clicked and affects a variable Menu_State with the encoder0Menu value
void doEncoderButton() {

  if (action_encoder == 0) {
    Menu_State = encoder0Menu ;

    if (encoder0Menu == 1) {
      action_encoder = 1 ;  
    }
  }

  else if (action_encoder == 1) {
    action_encoder = 0 ;
  }
  
}


void setup() {

  Serial.begin(9600);

  // encodeur rotatoire

  pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(digitalPinToInterrupt(3), doEncoder, RISING); 
  attachInterrupt(digitalPinToInterrupt(2), doEncoderButton, RISING); 

}



void loop() {

  Serial.print("Menu affiché : ");
  Serial.print(encoder0Menu);
  Serial.print(" Menu choisi : ");
  Serial.print(Menu_State);

  Serial.print(" Temps d'acquisition : ");
  Serial.println(temps_acquisition);

  // Il faut debounce et tout trop dur wola

}
