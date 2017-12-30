//PINES ARDUINO *********************************
const int pin_test = A3; // Pin de test/debug
/************************************************/
const int R_potPin =     A0; // Pin para regulación de velocidad motores TRASEROS vía potenciómetro
const int R_controlPin1 = 4; // motores TRASEROS pin 1 -> misma señal ambos motores
const int R_controlPin2 = 5; // motores TRASEROS pin 2 -> misma señal ambos motores
const int R_enablePin =   6 ; // motores TRASEROS- PIN DE ACTIVACIÓN

const int onOffSwitchStateSwitchPin = 12;   // MARCHA / PARO de motores
/* PIN 13 PARA SEÑALAR EL ARRANQUE/ PARADA DE LOS MOTORES
/************************************************/

//ESTADO DE MOTORES
boolean motorEnabled = 0; // Habilitación de motores en bloque
int R_motorSpeed = 0;   // Velocidad de motores TRASEROS
boolean motorDirection = 1; // Control de dirección de motores en bloque

/************************************************/
// PULSADORES 
//Estados iniciales de pulsadores
// Botón de arranque / parada
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;

void setup() {
  // Setup pines de PULSADORES
  /*pinMode(directionSwitchPin, INPUT);*/
  pinMode(onOffSwitchStateSwitchPin, INPUT);

  // Setup pines de MOTORES
  pinMode(R_enablePin, OUTPUT);
  pinMode(R_controlPin1, OUTPUT);
  pinMode(R_controlPin2, OUTPUT);
  
  // Motores apagados
  digitalWrite(R_enablePin, LOW);
}

void loop() {
  delay(10); //------------------------
  // leo estado de los botones y el potenciometro
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  
  //Como la entrada analógica del Arduino es de 10 bits, el rango va de 0 a 1023.
  //En cambio, la salidas del Arduino son de 8 bits (PWM), quiere decir, rango entre 0 a 255.
  //Por esta razón tenemos que dividir la lectura analógica por 2*2= 4
  R_motorSpeed = analogRead(R_potPin) / 4;

  //Detecto flancos ascendentes para cambiar velocidad y encendido motor
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH)
      motorEnabled = !motorEnabled;
  }
  //Control dirección de giro
  if (motorDirection == 1) {
    digitalWrite(R_controlPin1, HIGH);
    digitalWrite(R_controlPin2, LOW);
  }
  else {
    digitalWrite(R_controlPin1, LOW);
    digitalWrite(R_controlPin2, HIGH);
  }

  //Control encendido/apagado y velocidad con el pin enable del L293D
  if (motorEnabled == 1) {
    analogWrite(R_enablePin, R_motorSpeed);
  }
  else {
    analogWrite(R_enablePin, 0);
  }

  //Actualizar estados
  previousOnOffSwitchState = onOffSwitchState;
 
}
