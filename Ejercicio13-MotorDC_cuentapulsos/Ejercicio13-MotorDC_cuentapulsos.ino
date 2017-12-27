//PINES ARDUINO *********************************
/************************************************/
const int FR_pulse_pinD = 2;  // Lectura de encoder DELANTERO DERECHO (interrupt INT.0)
const int FL_pulse_pinD = 3 ; // Lectura de encoder DELANTERO IZQUIERDO (interrupt INT.1)

const int R_potPin =     A0; // Pin para regulación de velocidad motores TRASEROS vía potenciómetro
const int R_controlPin1 = 4; // motores TRASEROS pin 1 -> misma señal ambos motores
const int R_controlPin2 = 5; // motores TRASEROS pin 2 -> misma señal ambos motores
const int R_enablePin =   6 ; // motores TRASEROS- PIN DE ACTIVACIÓN

const int F_potPin =     A1; // Pin para regulación de velocidad motores DELANTEROS vía potenciómetro
const int F_controlPin1 = 7; // motores DELANTEROS pin 1 -> misma señal ambos motores
const int F_controlPin2 = 8; // motores DELANTEROS pin 2 -> misma señal ambos motores
const int F_enablePin =   9; // motores DELANTEROS- PIN DE ACTIVACIÓN

/*const int directionSwitchPin = 10;  // Cambio de dirección
/*const int directionSwitchPin_LED = 11;  // LED de marcha atrás PWM (para variar el brillo con la velocidad)
*/
const int onOffSwitchStateSwitchPin = 12;   // MARCHA / PARO de motores
/* PIN 13 PARA SEÑALAR EL ARRANQUE/ PARADA DE LOS MOTORES
/************************************************/

//ESTADO DE MOTORES
boolean motorEnabled = 0; // Habilitación de motores en bloque
int F_motorSpeed = 0;   // Velocidad de motores DELANTEROS
int R_motorSpeed = 0;   // Velocidad de motores TRASEROS
boolean motorDirection = 1; // Control de dirección de motores en bloque

unsigned long timeold = 0;    // Tiempo (ms)
int time_update = 1000;        // Tiempo de actualización (ms)
static volatile unsigned long debounce = 0; // Tiempo del rebote (microsegundos)

const int wheel_diameter = 65;   // Diámetro del cilindro (mm)

// LECTURA DE ENCODERS (optoacopladores)
int FR_pulses = 0;            // Contador de pulsos
int FR_pulse_state = 0;       // Estado inicial de pulsos
int FR_pulse_state_previous = 0;
unsigned int FR_pulsesperturn = 10; // Número de muescas que tiene el disco del encoder
unsigned int FR_rpm;                // Velocidad de rotación

int FL_pulses = 0;            // Contadores de pulsos
int FL_pulse_state = 0;       // Estado inicial de pulsos
int FL_pulse_state_previous = 0;
unsigned int FL_pulsesperturn = 1; // Número de muescas que tiene el disco del encoder
unsigned int FL_rpm;          // Velocidad de rotación
/************************************************/
// PULSADORES 
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
  pinMode(FL_pulses, INPUT);
  attachInterrupt(1, FR_counter, RISING); // Configuración de la interrupción 0 (pin 3) 
  FL_pulses = 0;
  FL_rpm = 0;

  // Setup pines de MOTORES
  pinMode(F_enablePin, OUTPUT);
  pinMode(F_controlPin1, OUTPUT);
  pinMode(F_controlPin2, OUTPUT);

  pinMode(R_enablePin, OUTPUT);
  pinMode(R_controlPin1, OUTPUT);
  pinMode(R_controlPin2, OUTPUT);
  
  // Motores apagados
  digitalWrite(F_enablePin, LOW);
  digitalWrite(R_enablePin, LOW);
}

////----------------INTERRUPCIONES -----------//////////////////////
 void FR_counter(){
  if(  digitalRead (FR_pulse_pinD) && (micros()-debounce > 500) && digitalRead (FR_pulse_pinD) ) { 
      // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        FR_pulses++;  // Suma el pulso bueno que entra.
  }
 }

  void FL_counter(){
  if(  digitalRead (FL_pulse_pinD) && (micros()-debounce > 500) && digitalRead (FL_pulse_pinD) ) { 
      // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        FL_pulses++;  // Suma el pulso bueno que entra.
  }
 }

void loop() {
  delay(10); //------------------------
  // leo estado de los botones y el potenciometro
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  //*directionSwitchState = digitalRead(directionSwitchPin);
  
  //Como la entrada analógica del Arduino es de 10 bits, el rango va de 0 a 1023.
  //En cambio, la salidas del Arduino son de 8 bits (PWM), quiere decir, rango entre 0 a 255.
  //Por esta razón tenemos que dividir la lectura analógica por 2*2= 4
  F_motorSpeed = analogRead(F_potPin) / 4;
  R_motorSpeed = analogRead(R_potPin) / 4;

  ///////////////////////////////////////////////
  // Detección y contador de pulsos
  // ENCODER DELANTERO DERECHO
  // Gestionado por interrupción 0 (pin 2)
  // ENCODER DELANTERO IZQUIERDO
  // Gestionado por interrupción 1 (pin 3)
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
    digitalWrite(F_controlPin1, HIGH);
    digitalWrite(F_controlPin2, LOW);
    digitalWrite(R_controlPin1, HIGH);
    digitalWrite(R_controlPin2, LOW);
  }
  else {
    digitalWrite(F_controlPin1, LOW);
    digitalWrite(F_controlPin2, HIGH);
    digitalWrite(R_controlPin1, LOW);
    digitalWrite(R_controlPin2, HIGH);
  }

  //Control encendido/apagado y velocidad con el pin enable del L293D
  if (motorEnabled == 1) {
    analogWrite(F_enablePin, F_motorSpeed);
    analogWrite(R_enablePin, R_motorSpeed);
  }
  else {
    analogWrite(F_enablePin, 0);
    analogWrite(R_enablePin, 0);
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
  
  Serial.print("\t Velocidad FRONT %");
  Serial.print((float)F_motorSpeed/255*100);
  Serial.print("\t Velocidad REAR %");
  Serial.print((float)R_motorSpeed/255*100);
  
  Serial.print("\t FR_pulses= ");
  Serial.print(FR_pulses);
  Serial.print("\t FL_pulses= ");
  Serial.print(FL_pulses);
  
  Serial.println();
  /*Serial.print("\t Dirección ");
  Serial.println(motorDirection);*/
}
