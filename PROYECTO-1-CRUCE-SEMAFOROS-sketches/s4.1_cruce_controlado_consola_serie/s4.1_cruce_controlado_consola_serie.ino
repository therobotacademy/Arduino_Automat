/***   Global variables   ***/
// ESTADO DEL CRUCE
int estado=1;
// TIEMPOS DE ESTADO
float t_ciclo = 10000; // Tiempo total del ciclo
float E1normal= 0.45;
float E2normal= 0.15;
float E3normal= 0.25;
float E4normal= 0.15;
float E1punta= 0.60;
float E2punta= 0.10;
float E3punta= 0.20;
float E4punta= 0.10;
float E1;
float E2;
float E3;
float E4;
// CONEXIONES DE PINES A LEDs
int P_ROJO_PIN=8;
int P_AMARILLO_PIN=10;
int P_VERDE_PIN=12;
int S_ROJO_PIN=2;
int S_AMARILLO_PIN=4;
int S_VERDE_PIN=6;
// SI QUIERES AHORRAR ESPACIO EN VARIABLES
// Pines semáforo principal
//#define P_RED_PIN 8
//#define P_YELLOW_PIN 10
//#define P_GREEN_PIN 12
// Pines semáforo secundario
//#define S_RED_PIN 2
//#define S_YELLOW_PIN 4
//#define S_GREEN_PIN 6

// Control de condición horario normal / punta
String input_condicion = "";  // Nueva condición introducida por consola
String condicion = "normal";  // Por defecto regulación por horario 'normal'. El alternativo es 'punta'

/***   Function declaration
semaforo = 'principal' ó 'secundario'
rojo, amarillo, verde = 1 (ENCENDIDO) / 0 (APAGADO)
***/
void ciclo_semaforo (String semaforo, int rojo, int amarillo, int verde);

void setup()
{
  Serial.begin(9600);
  Serial.println("Condición actual = \"" + condicion + "\"");
  Serial.println("\n Cambio de regulacion (normal/punta) (en otro caso mantiene estado)-> ");
  
  pinMode(P_ROJO_PIN,OUTPUT);
  pinMode(P_AMARILLO_PIN,OUTPUT);
  pinMode(P_VERDE_PIN,OUTPUT);
  pinMode(S_ROJO_PIN,OUTPUT);
  pinMode(S_AMARILLO_PIN,OUTPUT);
  pinMode(S_VERDE_PIN,OUTPUT);
  
  // Condición inicial de regulación
  E1=t_ciclo*E1normal;
  E2=t_ciclo*E2normal;
  E3=t_ciclo*E3normal;
  E4=t_ciclo*E4normal;
}


void loop()
{
  // CAMBIO DE CICLO DE REGULACIÓN POR CONSOLA
  // Introduce normal ó punta
    if (Serial.available() > 0) {
      input_condicion = ""; //vacio lo leido
      Serial.println("Cambio de regulacion (normal/punta) (en otro caso mantiene estado)-> ");
      do {
        char caracter_leido;
        delay(5);
        caracter_leido = Serial.read();
        input_condicion += caracter_leido;
      }  while (Serial.available() > 0);

      Serial.println("Nueva condición de regulación de horario: \"" + input_condicion + "\"");

      if (input_condicion.startsWith("punta")) {
        condicion = "punta";
        digitalWrite(LED_BUILTIN, LOW);
      }
      else {
        condicion = "normal";
        digitalWrite(LED_BUILTIN, HIGH); // Señalizamos con el LED interno (pin 13)            
        }
      }
    
    if (condicion == "punta") {
      E1=t_ciclo*E1punta;
      E2=t_ciclo*E2punta;
      E3=t_ciclo*E3punta;
      E4=t_ciclo*E4punta;
    }
    else {
      E1=t_ciclo*E1normal;
      E2=t_ciclo*E2normal;
      E3=t_ciclo*E3normal;
      E4=t_ciclo*E4normal;
    }
    
    // CAMBIOS DE ESTADO DEL CRUCE
    Serial.print("\t Estado E"); Serial.print(estado); Serial.print(" ");
    switch (estado)
    {
      case 1:
      {
        ciclo_semaforo("principal", 0, 0, 1);
        ciclo_semaforo("secundario", 1, 0, 0);
        Serial.print(E1); Serial.print(" ms"); Serial.print(" ");
        delay(E1);
        break;
      }
      case 2:
      {
        ciclo_semaforo("principal", 0, 1, 0);
        ciclo_semaforo("secundario", 1, 0, 0);
        Serial.print(E2); Serial.print(" ms"); Serial.print(" ");
        delay(E2);
        break;
      }
      case 3:
      {
        ciclo_semaforo("principal", 1, 0, 0);
        ciclo_semaforo("secundario", 0, 0, 1);
        Serial.print(E3); Serial.print(" ms"); Serial.print(" ");
        delay(E3);
        break;
      }
      case 4:
      {
        ciclo_semaforo("principal", 1, 0, 0);
        ciclo_semaforo("secundario", 0, 1, 0);
        Serial.print(E4); Serial.print(" ms"); Serial.print("\n");
        delay(E4);
        break;
      }
      default:
      {
        estado=1;
      }
    }
    // TRANSICIÓN AL SIGUIENTE ESTADO
    estado=estado + 1;
    if (estado > 4) {
      estado=1;
     }
}

/***   Function definition   ***/
void ciclo_semaforo (String semaforo, int rojo, int amarillo, int verde) {

  if (semaforo == "principal") {
    if (rojo == 1)
      digitalWrite(P_ROJO_PIN,HIGH);
    else
      digitalWrite(P_ROJO_PIN,LOW);
    if (amarillo == 1)
      digitalWrite(P_AMARILLO_PIN,HIGH);
    else
      digitalWrite(P_AMARILLO_PIN,LOW);
    if (verde == 1)
      digitalWrite(P_VERDE_PIN,HIGH);
    else
      digitalWrite(P_VERDE_PIN,LOW);
   }
  if (semaforo == "secundario") {
    if (rojo == 1)
      digitalWrite(S_ROJO_PIN,HIGH);
    else
      digitalWrite(S_ROJO_PIN,LOW);
    if (amarillo == 1)
      digitalWrite(S_AMARILLO_PIN,HIGH);
    else
      digitalWrite(S_AMARILLO_PIN,LOW);
    if (verde == 1)
      digitalWrite(S_VERDE_PIN,HIGH);
    else
      digitalWrite(S_VERDE_PIN,LOW);
    
   }
 }
