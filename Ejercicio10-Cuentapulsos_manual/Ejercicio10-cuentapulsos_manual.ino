// this constant won't change:
const int  buttonPin = 11;    // the pin that the pushbutton is attached to
const int ledPin = 12;       // the pin that the LED is attached to
const int led_freq_pushes= 2; // Frequency of change of LED state in function of number of pushes
int estadoLed = 0;           // LED is off at starting

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT_PULLUP); //Internal pullup resistor (LOW when button is pressed)
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); //Inicialmente apagado
  // initialize serial communication:
  Serial.begin(9600);
  lastButtonState = digitalRead(buttonPin); //inicializo el estado del pulsador
}

void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  delay(50);  // --------------------
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      buttonPushCounter++;
      Serial.print("nº pulsos: ");
      Serial.print(buttonPushCounter);
      Serial.print("\t resto= "); 
      Serial.print(buttonPushCounter % led_freq_pushes);
      Serial.print("\t Flanco Descendente\t");
      // Check pushes to activate LED every 'led_freq_pushes' pushes ('led_freq_pushes' ON y 'led_freq_pushes' OFF)
      if (buttonPushCounter % led_freq_pushes == 0) {
        estadoLed = !estadoLed; // Change the state of the LED every 'led_freq_pushes' pushes
      }
      digitalWrite(ledPin, estadoLed);
      estadoLed ? Serial.print("LED ENCENDIDO") : Serial.print("LED APAGADO"); //Operador ternario
    }
    else {
      Serial.println("\t Flanco Ascendente");
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}
