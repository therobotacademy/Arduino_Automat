//Pines
// FR_: pines para motor DELANTERO - LADO DERECHO
const int FR_enablePin = 6; // motor DELANTERO (derecho) PIN DE ACTIVACIÓN
const int FR_controlPin1 = 7; // motor delantero (derecho) pin 1 -> señal a motor trasero
const int FR_controlPin2 = 8; // motor delantero (derecho) pin 2 -> señal a motor trasero
// RR_: pines para motor TRASERO - LADO DERECHO
const int RR_enablePin = 9 ; // motor TRASERO (derecho) PIN DE ACTIVACIÓN

//*const int directionSwitchPin = 9;
const int onOffSwitchStateSwitchPin = 10;

const int potPin = A0;

//Estados botones
// Botón de arranque / parada
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
/*int directionSwitchState = 0;
int previousDirectionSwitchState = 0;
*/
//Estados Motor
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
  Serial.begin(9600);
  //Botones
  //pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  
  //Motor
  pinMode(FR_enablePin, OUTPUT);
  pinMode(FR_controlPin1, OUTPUT);
  pinMode(FR_controlPin2, OUTPUT);
  pinMode(RR_enablePin, OUTPUT);
  //Motor apagado
  digitalWrite(FR_enablePin, LOW);
  digitalWrite(RR_enablePin, LOW);
}

void loop() {
  // leo estado de los botones y el potenciometro
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(50);
  //*directionSwitchState = digitalRead(directionSwitchPin);
  
  //Como la entrada analógica del Arduino es de 10 bits, el rango va de 0 a 1023.
  //En cambio, la salidas del Arduino son de 8 bits (PWM), quiere decir, rango entre 0 a 255.
  //Por esta razón tenemos que dividir la lectura analógica por 2*2= 4
  motorSpeed = analogRead(potPin) / 4;

  //Detecto flancos ascendentes para cambiar velocidad y encendido motor
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH)
      motorEnabled = !motorEnabled;
  }
  if (motorEnabled == 1)
    digitalWrite(LED_BUILTIN, HIGH); // Iluminamos el LED interno si el mecanismo está activo
    else
    digitalWrite(LED_BUILTIN, LOW);
  
  /*if (directionSwitchState != previousDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }*/

  //Control dirección de giro
  if (motorDirection == 1) {
    digitalWrite(FR_controlPin1, HIGH);
    digitalWrite(FR_controlPin2, LOW);
  }
  else {
    digitalWrite(FR_controlPin1, LOW);
    digitalWrite(FR_controlPin2, HIGH);
  }

  //Control encendido/apagado y velocidad con el pin enable del L293D
  if (motorEnabled == 1) {
    analogWrite(FR_enablePin, motorSpeed);
    analogWrite(RR_enablePin, motorSpeed);
  }
  else {
    analogWrite(FR_enablePin, 0);
    analogWrite(RR_enablePin, 0);
  }

  //Actualizar estados
  previousOnOffSwitchState = onOffSwitchState;
  /*previousDirectionSwitchState = directionSwitchState;
    */
  
  //Imprimo por el Puerto Serie / Serial Plotter
  Serial.print("\t PULSADO ");
  Serial.print(onOffSwitchState);
  Serial.print("  Activado ");
  Serial.print(motorEnabled);
  Serial.print("\t Velocidad %");
  Serial.print((float)motorSpeed/255*100);
  Serial.print("\t Dirección ");
  Serial.println(motorDirection);

}
