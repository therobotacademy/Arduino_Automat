//PINES ARDUINO *********************************
// Pin para regulación de velocidad de motores vía potenciómetro
const int potPin = A0;
/************************************************/
// FR_: pines para motor DELANTERO - LADO DERECHO
const int FR_enablePin = 6; // motor DELANTERO (derecho) PIN DE ACTIVACIÓN
const int FR_controlPin1 = 7; // motor delantero (derecho) pin 1 -> misma señal a motor trasero (derecho)
const int FR_controlPin2 = 8; // motor delantero (derecho) pin 2 -> misma señal a motor trasero (derecho)

// RR_: pines para motor TRASERO - LADO DERECHO
const int RR_enablePin = 9 ; // motor TRASERO (derecho) PIN DE ACTIVACIÓN
/************************************************/

//ESTADO DE MOTORES
int motorEnabled = 0; //----- F(ront) para ambos delanteros F_motorEnabled
int motorSpeed = 0;   //----- "
int motorDirection = 1; //----- "

unsigned long timeold = 0;    // Tiempo
int time_update = 1000;        // Tiempo de actualización (ms)
static volatile unsigned long debounce = 0; // Tiempo del rebote
const int wheel_diameter = 65;   // Diámetro del cilindro (mm)

// LECTURA DE ENCODERS (optoacopladores)
const int FR_pulse_pinD = 2;  // Lectura de encoder DELANTERO DERECHO (interrupt INT.0)
int FR_pulses = 0;            // Contador de pulsos
int FR_pulse_state = 0;       // Estado inicial de pulsos
int FR_pulse_state_previous = 0;
unsigned int FR_pulsesperturn = 10; // Número de muescas que tiene el disco del encoder
unsigned int FR_rpm;                // Velocidad de rotación

const int RR_pulse_pinD = 3 ; // Lectura de encoder TRASERO DERECHO (interrupt INT.1)
int RR_pulses = 0;            // Contadores de pulsos
int RR_pulse_state = 0;       // Estado inicial de pulsos
int RR_pulse_state_previous = 0;
unsigned int RR_pulsesperturn = 1; // Número de muescas que tiene el disco del encoder
unsigned int RR_rpm;          // Velocidad de rotación
/************************************************/
// PULSADORES 
/*const int directionSwitchPin = 9;  // Cambio de dirección*/
const int onOffSwitchStateSwitchPin = 10;   // MARCHA / PARO de motores
//Estados iniciales de pulsadores
// Botón de arranque / parada
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
/*int directionSwitchState = 0;
int previousDirectionSwitchState = 0;
*/

void setup() {
  Serial.begin(9600);
  // Setup pines de PULSADORES
  /*pinMode(directionSwitchPin, INPUT);*/
  pinMode(onOffSwitchStateSwitchPin, INPUT);

  // Setup de ENCODERS (optoacopladores)
  timeold = 0;
  pinMode(FR_pulses, INPUT);
  attachInterrupt(0, FR_counter, RISING); // Configuración de la interrupción 0 (pin 2)
  FR_pulses = 0;
  FR_rpm = 0;
  pinMode(RR_pulses, INPUT);
  attachInterrupt(1, FR_counter, RISING); // Configuración de la interrupción 0 (pin 3) 
  RR_pulses = 0;
  RR_rpm = 0;

  // Setup pines de MOTORES
  pinMode(FR_enablePin, OUTPUT);
  pinMode(FR_controlPin1, OUTPUT);
  pinMode(FR_controlPin2, OUTPUT);
  pinMode(RR_enablePin, OUTPUT);
  // Motores apagados
  digitalWrite(FR_enablePin, LOW);
  digitalWrite(RR_enablePin, LOW);
}

////----------------INTERRUPCIONES -----------//////////////////////
 void FR_counter(){
  if(  digitalRead (FR_pulse_pinD) && (micros()-debounce > 500) && digitalRead (FR_pulse_pinD) ) { 
      // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        FR_pulses++;  // Suma el pulso bueno que entra.
  }
 }


void loop() {
  delay(10);
  // leo estado de los botones y el potenciometro
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  //*directionSwitchState = digitalRead(directionSwitchPin);
  
  //Como la entrada analógica del Arduino es de 10 bits, el rango va de 0 a 1023.
  //En cambio, la salidas del Arduino son de 8 bits (PWM), quiere decir, rango entre 0 a 255.
  //Por esta razón tenemos que dividir la lectura analógica por 2*2= 4
  motorSpeed = analogRead(potPin) / 4;

  ///////////////////////////////////////////////
  // Detección y contador de pulsos
  // ENCODER DELANTERO DERECHO
  FR_pulse_state = digitalRead(FR_pulse_pinD);
  int FR_pulse_pinA=analogRead(A3); ///////////////////////////////////
  /*if (FR_pulse_state != FR_pulse_state_previous) {
    if (FR_pulse_state == 1){
      FR_pulses++;
    }
  }
  FR_pulse_state_previous = FR_pulse_state;*/
  // ENCODER TRASERO DERECHO
  RR_pulse_state = digitalRead(RR_pulse_pinD);
  int RR_pulse_pinA=analogRead(A4); //////////////////////////////////
  if (RR_pulse_state != RR_pulse_state_previous) {
    if (RR_pulse_state == 1){
      RR_pulses++;
    }
  }
  RR_pulse_state_previous = RR_pulse_state;
  //////////////////////////////////////////////

  //Detecto flancos ascendentes para cambiar velocidad y encendido motor
  if (onOffSwitchState != previousOnOffSwitchState) {
    if (onOffSwitchState == HIGH)
      motorEnabled = !motorEnabled;
  }
  if (motorEnabled == 1) {
    digitalWrite(LED_BUILTIN, HIGH); // Iluminamos el LED interno si el mecanismo está activo
    Serial.print("Mecanismo ACTIVO\t");
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Mecanismo DESCONECTADO\t");
  }
  
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
  
  Serial.print("\t");
  Serial.print(FR_pulse_pinD);
  Serial.print(" ");
  Serial.print(FR_pulse_pinA);
  Serial.print(" ");
  Serial.print(FR_pulse_state);
  Serial.print(" FR_pulses= ");
  Serial.print(FR_pulses);
  
  Serial.print("\t");
  Serial.print(RR_pulse_pinD);
  Serial.print(" ");
  Serial.print(RR_pulse_pinA);
  Serial.print(" ");
  Serial.print(RR_pulse_state);
  Serial.print(" RR_pulses= ");
  Serial.print(RR_pulses);
  Serial.println();
  /*Serial.print("\t Dirección ");
  Serial.println(motorDirection);*/
}
