// Pines semáforo principal
#define P_RED_PIN 8
#define P_YELLOW_PIN 10
#define P_GREEN_PIN 12

// Pines semáforo secundario
#define S_RED_PIN 2
#define S_YELLOW_PIN 4
#define S_GREEN_PIN 6

int n_ciclo = 1;
// Estado del cruce
int estado = 0; 

// Factor de escala de tiempos de estado
float speed_ = 1;

// Tiempos de estado (referencia)
int E1 = 4500;
int E2 = 1500;

int E3 = 2500;
int E4 = 1500;

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
  switch (estado) {
    case 1:
      // ESTADO E1: Coches circulando en vía PRINCIPAL
      // En E1 indicamos el nº de ciclo
      Serial.print("nº ciclo "); Serial.print(n_ciclo); Serial.print("\t");
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
      // ESTADO E3: Coches circulando en vía SECUNDARIA
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, HIGH); digitalWrite(P_YELLOW_PIN, LOW); digitalWrite(P_GREEN_PIN, LOW);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, LOW); digitalWrite(S_YELLOW_PIN, LOW); digitalWrite(S_GREEN_PIN, HIGH);
      // Volcado de info al puerto serie
      Serial.print(E3*speed_); Serial.print(" ms"); Serial.print(estado); Serial.print(" \t");
      delay(E3*speed_);
      break;
    case 4:
      // ESTADO E4: Transición a vía PRINCIPAL
      // Vía PRINCIPAL
      digitalWrite(P_RED_PIN, HIGH); digitalWrite(P_YELLOW_PIN, LOW); digitalWrite(P_GREEN_PIN, LOW);
      // Vía SECUNDARIA
      digitalWrite(S_RED_PIN, LOW); digitalWrite(S_YELLOW_PIN, HIGH); digitalWrite(S_GREEN_PIN, LOW);
      // Volcado de info al puerto serie
      Serial.print(E4*speed_); Serial.print(" ms"); Serial.print(estado); Serial.print(" \n");
      delay(E4*speed_);
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
  n_ciclo++;
  estado++; // Transición al siguiente estado
  if (estado > 4) {
    estado = 1; // Nuevo ciclo del cruce
  }
}
