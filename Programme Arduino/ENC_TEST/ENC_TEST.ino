// encoder

#define encoder0PinA  3  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 2 // Switch connection if available
volatile unsigned int encoder0Menu_temp = 0;
volatile unsigned int encoder0Menu = 0;
volatile unsigned int Menu_State = 0 ;

volatile unsigned int action_encoder = 0; // retient quelle action effectuer pour l'encodeur
volatile unsigned int temps_acquisition_temp = 0;
volatile unsigned int temps_acquisition = 0;

int State;
int Old_State;

  // Fonctions Encodeur

// doEncoder increments or decrements the variable encoder0Menu that is used to set and chose actions, between 4 of them
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

  else if (action_encoder == 1) {

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

  pinMode(Switch, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(3), doEncoder, RISING); 
  attachInterrupt(digitalPinToInterrupt(2), doEncoderButton, FALLING); 

}



void loop() {

  Serial.print("Menu affiché : ");
  Serial.print(encoder0Menu);
  Serial.print(" Menu choisi : ");
  Serial.print(Menu_State);

  Serial.print(" Temps d'acquisition : ");
  Serial.println(temps_acquisition);

  // ENCODEUR OK !

}
