// Pines semáforo principal
#define P_RED_PIN 8
#define P_YELLOW_PIN 10
#define P_GREEN_PIN 12

// Pines semáforo secundario
#define S_RED_PIN 2
#define S_YELLOW_PIN 4
#define S_GREEN_PIN 6

// Tiempos semáforo PRINCIPAL
int P_red_on = 1000;
int P_yellow_on = 500;
int P_green_on = 1500;

// Tiempos semáforo SECUNDARIO
int S_red_on = 500;
int S_yellow_on = 250;
int S_green_on = 750;

void setup() {
  // puertos a los que están conectados los LED - salidas
  pinMode(P_RED_PIN, OUTPUT);
  pinMode(P_YELLOW_PIN, OUTPUT);
  pinMode(P_GREEN_PIN, OUTPUT);
  pinMode(S_RED_PIN, OUTPUT);
  pinMode(S_YELLOW_PIN, OUTPUT);
  pinMode(S_GREEN_PIN, OUTPUT);
}

void loop() {
  // SEMÁFORO DE LA VÍA PRINCIPAL
  //Luz roja
  digitalWrite(P_RED_PIN, HIGH);
  delay(P_red_on);
  digitalWrite(P_RED_PIN, LOW);
  //Luz verde
  digitalWrite(P_GREEN_PIN, HIGH);
  delay(P_green_on);
  digitalWrite(P_GREEN_PIN, LOW);
  //Luz amarilla
  digitalWrite(P_YELLOW_PIN, HIGH);
  delay(P_yellow_on);
  digitalWrite(P_YELLOW_PIN, LOW);
  
  // SEMÁFORO DE LA VÍA SECUNDARIA
  //Luz roja
  digitalWrite(S_RED_PIN, HIGH);
  delay(S_red_on);
  digitalWrite(S_RED_PIN, LOW);
  //Luz verde
  digitalWrite(S_GREEN_PIN, HIGH);
  delay(S_green_on);
  digitalWrite(S_GREEN_PIN, LOW);
  //Luz amarilla
  digitalWrite(S_YELLOW_PIN, HIGH);
  delay(S_yellow_on);
  digitalWrite(S_YELLOW_PIN, LOW);
}
