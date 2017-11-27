// Pines semáforo principal
#define P_RED_PIN 8
#define P_YELLOW_PIN 10
#define P_GREEN_PIN 12

// Pines semáforo secundario
#define S_RED_PIN 2
#define S_YELLOW_PIN 4
#define S_GREEN_PIN 6

// Estado del cruce
int estado = 1;
int estado_previo = 1;

// Factor de escala de tiempos de estado
float speed_ = 1;

// Tiempos de estado (referencia)
int E1 = 4000;
int E2 = 1500;
int E3 = 1000;
int E4 = 2000;
int E5 = 1500;

void setup() {
  Serial.begin(9600);
  //Estado inicial
  estado = 1;
  // puertos a los que están conectados los LED - salidas
  pinMode(P_RED_PIN, OUTPUT);
  pinMode(P_YELLOW_PIN, OUTPUT);
  pinMode(P_GREEN_PIN, OUTPUT);
  pinMode(S_RED_PIN, OUTPUT);
  pinMode(S_YELLOW_PIN, OUTPUT);
  pinMode(S_GREEN_PIN, OUTPUT);
}

void loop() {
  Serial.print("Estado "); Serial.print(estado); Serial.print(" ");
  
  // EJECUCIÓN DE ESTADO
  switch (estado) {
    case 1:
      // ESTADO E1: Coches circulando en vía PRINCIPAL
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, LOW); digitalWrite(P_YELLOW_PIN, LOW); digitalWrite(P_GREEN_PIN, HIGH);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, HIGH); digitalWrite(S_YELLOW_PIN, LOW); digitalWrite(S_GREEN_PIN, LOW);
      // Volcado de info al puerto serie
      Serial.print(E1*speed_); Serial.print(" ms"); Serial.print(" \t");
      delay(E1*speed_);
      break;
    case 2:
      // ESTADO E2: Transición a vía SECUNDARIA
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, LOW); digitalWrite(P_YELLOW_PIN, HIGH); digitalWrite(P_GREEN_PIN, LOW);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, HIGH); digitalWrite(S_YELLOW_PIN, LOW); digitalWrite(S_GREEN_PIN, LOW);
      // Volcado de info al puerto serie
      Serial.print(E1*speed_); Serial.print(" ms"); Serial.print(estado); Serial.print(" \t");
      delay(E2*speed_);
      break;

    case 3:
      // ESTADO E3: Colchón de seguridad en la transición (2 semáforos en rojo)
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, HIGH); digitalWrite(P_YELLOW_PIN, LOW); digitalWrite(P_GREEN_PIN, LOW);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, HIGH); digitalWrite(S_YELLOW_PIN, LOW); digitalWrite(S_GREEN_PIN, LOW);
      // Volcado de info al puerto serie
      Serial.print(E3*speed_); Serial.print(" ms"); Serial.print(estado); Serial.print(" \t");
      delay(E3*speed_);
      break;
      
    case 4:
      // ESTADO E4: Coches circulando en vía SECUNDARIA
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, HIGH); digitalWrite(P_YELLOW_PIN, LOW); digitalWrite(P_GREEN_PIN, LOW);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, LOW); digitalWrite(S_YELLOW_PIN, LOW); digitalWrite(S_GREEN_PIN, HIGH);
      // Volcado de info al puerto serie
      Serial.print(E4*speed_); Serial.print(" ms"); Serial.print(estado); Serial.print(" \t");
      delay(E4*speed_);
      break;
    case 5:
      // ESTADO E5: Transición a vía PRINCIPAL
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, HIGH); digitalWrite(P_YELLOW_PIN, LOW); digitalWrite(P_GREEN_PIN, LOW);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, LOW); digitalWrite(S_YELLOW_PIN, HIGH); digitalWrite(S_GREEN_PIN, LOW);
      // Volcado de info al puerto serie
      Serial.print(E5*speed_); Serial.print(" ms"); Serial.print(estado); Serial.print(" \n");
      delay(E5*speed_);
      break;   
    default:
      // turn all the LEDs on:
      for (int thisPin = 2; thisPin < 13; thisPin+=2) {
          digitalWrite(thisPin, LOW);
          Serial.print(thisPin); Serial.print(" ");
          delay(200);
        }
        Serial.println(" ");
  }
  
// DECISIÓN SOBRE EL SIGUIENTE ESTADO
if (estado==3 && estado_previo==5) {
  estado = 1;
  estado_previo = 3;
  }
else {
  estado_previo = estado;
  estado++; // Transición al siguiente estado
  if (estado > 5) {
    estado = 3; // Transición a estado de retardo de seguridad
    }
  }
}
