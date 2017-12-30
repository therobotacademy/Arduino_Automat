//PINES ARDUINO *********************************
/************************************************/
const int RL_pulse_pinD = 2;  // Lectura de encoder DELANTERO DERECHO (interrupt INT.0)
const int RR_pulse_pinD = 3 ; // Lectura de encoder DELANTERO IZQUIERDO (interrupt INT.1)

const int R_potPin =     A0; // Pin para regulación de velocidad motores TRASEROS vía potenciómetro
const int R_controlPin1 = 4; // motores TRASEROS pin 1 -> misma señal ambos motores
const int R_controlPin2 = 5; // motores TRASEROS pin 2 -> misma señal ambos motores
const int R_enablePin =   6 ; // motores TRASEROS- PIN DE ACTIVACIÓN

const int F_potPin =     A1; // Pin para regulación de velocidad motores DELANTEROS vía potenciómetro
const int F_controlPin1 = 7; // motores DELANTEROS pin 1 -> misma señal ambos motores
const int F_controlPin2 = 8; // motores DELANTEROS pin 2 -> misma señal ambos motores
const int F_enablePin =   9; // motores DELANTEROS- PIN DE ACTIVACIÓN

const int directionSwitchPin = 10;  // Cambio de dirección
const int directionSwitchPin_LED = 11;  // LED de marcha atrás PWM (para variar el brillo con la velocidad)

const int onOffSwitchStateSwitchPin = 12;   // MARCHA / PARO de motores
/* PIN 13 PARA SEÑALAR EL ARRANQUE/ PARADA DE LOS MOTORES
/************************************************/

//ESTADO DE MOTORES
boolean motorEnabled = 0; // Habilitación de motores en bloque
byte F_motorSpeed = 0;   // Velocidad de motores DELANTEROS
byte R_motorSpeed = 0;   // Velocidad de motores TRASEROS
boolean motorDirection = 1; // Control de dirección de motores en bloque

unsigned long timeold = 0;    // Tiempo (ms)
int time_update = 1000;        // Tiempo de actualización (ms)
static volatile unsigned long debounce = 0; // Tiempo del rebote (microsegundos)

const int wheel_diameter = 65;   // Diámetro del cilindro (mm)

// LECTURA DE ENCODERS (optoacopladores)
int RL_pulses = 0;            // Contador de pulsos
int RL_pulse_state = 0;       // Estado inicial de pulsos
int RL_pulse_state_previous = 0;
unsigned int RL_pulsesperturn = 4; // Número de muescas que tiene el disco del encoder
unsigned int RL_rpm;                // Velocidad de rotación

int RR_pulses = 0;            // Contadores de pulsos
int RR_pulse_state = 0;       // Estado inicial de pulsos
int RR_pulse_state_previous = 0;
unsigned int RR_pulsesperturn = 20; // Número de muescas que tiene el disco del encoder
unsigned int RR_rpm;          // Velocidad de rotación
/************************************************/
// PULSADORES 
//Estados iniciales de pulsadores
// Botón de arranque / parada
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 1;         // Para que inicialmente los motores vayan hacia adelante
int previousDirectionSwitchState = 1;
byte brillo = 0; // Brillo proporcional a velocidad de motores

void setup() {
  Serial.begin(9600);
  // Setup pines de PULSADORES
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(directionSwitchPin, INPUT_PULLUP); //Internal pullup resistor (LOW when button is pressed)
  motorDirection = 1; // Motores avanzando hacia adelante inicialmente
  // Setup de ENCODERS (optoacopladores)
  timeold = 0;
  pinMode(RL_pulses, INPUT);
  attachInterrupt(0, RL_counter, RISING); // Configuración de la interrupción 0 (pin 2)
  RL_pulses = 0;
  RL_rpm = 0;
  pinMode(RR_pulses, INPUT);
  attachInterrupt(1, RR_counter, RISING); // Configuración de la interrupción 0 (pin 3) 
  RR_pulses = 0;
  RR_rpm = 0;

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
 void RL_counter(){
  if(  digitalRead (RL_pulse_pinD) && (micros()-debounce > 500) && digitalRead (RL_pulse_pinD) ) { 
      // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        RL_pulses++;  // Suma el pulso bueno que entra.
  }
 }

  void RR_counter(){
  if(  digitalRead (RR_pulse_pinD) && (micros()-debounce > 500) && digitalRead (RR_pulse_pinD) ) { 
      // Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 1000 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        RR_pulses++;  // Suma el pulso bueno que entra.
  }
 }

void loop() {
  delay(10); //------------------------
  // leo estado de los botones y el potenciometro
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  directionSwitchState = digitalRead(directionSwitchPin);
  
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
 
  if (directionSwitchState != previousDirectionSwitchState) {
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }

  //Control dirección de giro
  if (motorDirection == 1) {
    digitalWrite(F_controlPin1, HIGH);
    digitalWrite(F_controlPin2, LOW);
    digitalWrite(R_controlPin1, HIGH);
    digitalWrite(R_controlPin2, LOW);
    analogWrite(directionSwitchPin_LED, 0);
  }
  else {
    digitalWrite(F_controlPin1, LOW);
    digitalWrite(F_controlPin2, HIGH);
    digitalWrite(R_controlPin1, LOW);
    digitalWrite(R_controlPin2, HIGH);
    brillo = (R_motorSpeed + F_motorSpeed)/2;
    analogWrite(directionSwitchPin_LED, brillo);
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
  previousDirectionSwitchState = directionSwitchState;
  
  //Imprimo por el Puerto Serie
  if (motorEnabled == 1) {
    digitalWrite(LED_BUILTIN, HIGH); // Iluminamos el LED interno si el mecanismo está activo
    Serial.print("Mecanismo ACTIVO");
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Mecanismo DESCONECTADO");
  }
  Serial.print(" ");
  Serial.print(motorEnabled);
  
  Serial.print("\t PULSADO ");
  Serial.print(onOffSwitchState);

  Serial.print("\t Velocidad FRONT %");
  Serial.print((float)F_motorSpeed/255*100);
  Serial.print("\t Velocidad REAR %");
  Serial.print((float)R_motorSpeed/255*100);
  
  Serial.print("\t RL_pulses= ");
  Serial.print(RL_pulses);
  Serial.print("\t RR_pulses= ");
  Serial.print(RR_pulses);
  
  Serial.print("\t Dirección ");
  Serial.println(motorDirection);
}
