// Pines semáforo principal
#define P_RED_PIN 8
#define P_YELLOW_PIN 10
#define P_GREEN_PIN 12

// Pines semáforo secundario
#define S_RED_PIN 2
#define S_YELLOW_PIN 4
#define S_GREEN_PIN 6

// Factor de escala de tiempos de estado
float speed_ = 1;

// Tiempos de estado (referencia)
int E1 = 4500;
int E2 = 1500;

int E3 = 2500;
int E4 = 1500;

void setup() {
  Serial.begin(9600);
  // puertos a los que están conectados los LED - salidas
  pinMode(P_RED_PIN, OUTPUT);
  pinMode(P_YELLOW_PIN, OUTPUT);
  pinMode(P_GREEN_PIN, OUTPUT);
  pinMode(S_RED_PIN, OUTPUT);
  pinMode(S_YELLOW_PIN, OUTPUT);
  pinMode(S_GREEN_PIN, OUTPUT);
}

void loop() {
  // ESTADO E1: Coches circulando en vía PRINCIPAL
  // Vía PRINCIPAL
  digitalWrite(P_RED_PIN, LOW);
  digitalWrite(P_YELLOW_PIN, LOW);
  digitalWrite(P_GREEN_PIN, HIGH);
  // Vía SECUNDARIA
  digitalWrite(S_RED_PIN, HIGH);
  digitalWrite(S_YELLOW_PIN, LOW);
  digitalWrite(S_GREEN_PIN, LOW);
  Serial.print("E1 (ms)= ");
  Serial.print(E1*speed_);
  Serial.print(" \t");
  delay(E1*speed_);

  // ESTADO E2: Transición a vía SECUNDARIA
  // Vía PRINCIPAL
  //digitalWrite(P_RED_PIN, LOW);
  digitalWrite(P_YELLOW_PIN, HIGH);
  digitalWrite(P_GREEN_PIN, LOW);
  // Vía SECUNDARIA
  //digitalWrite(S_RED_PIN, HIGH);
  //digitalWrite(S_YELLOW_PIN, LOW);
  //digitalWrite(S_GREEN_PIN, LOW);
  Serial.print("E2 (ms)= ");
  Serial.print(E2*speed_);
  Serial.print(" \t");
  delay(E2*speed_);

  // ESTADO E3: Coches circulando en vía SECUNDARIA
  // Vía PRINCIPAL
  digitalWrite(P_RED_PIN, HIGH);
  digitalWrite(P_YELLOW_PIN, LOW);
  //digitalWrite(P_GREEN_PIN, LOW);
  // Vía SECUNDARIA
  digitalWrite(S_RED_PIN, LOW);
  //digitalWrite(S_YELLOW_PIN, LOW);
  digitalWrite(S_GREEN_PIN, HIGH);
  Serial.print("E3 (ms)= ");
  Serial.print(E3*speed_);
  Serial.print(" \t");
  delay(E3*speed_);

  // ESTADO E4: Transición a vía PRINCIPAL
  // Vía PRINCIPAL
  //digitalWrite(P_RED_PIN, HIGH);
  //digitalWrite(P_YELLOW_PIN, LOW);
  //digitalWrite(P_GREEN_PIN, LOW);
  // Vía SECUNDARIA
  //digitalWrite(S_RED_PIN, LOW);
  digitalWrite(S_YELLOW_PIN, HIGH);
  digitalWrite(S_GREEN_PIN, LOW);
  Serial.print("E4 (ms)= ");
  Serial.println(E4*speed_);
  delay(E4*speed_);
}
