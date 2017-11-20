#define RED_PIN 8
#define YELLOW_PIN 10
#define GREEN_PIN 12

// crea variables que almacenan el tiempo de retardo para cada fase en milisegundos
// int - tipo de datos, enteros de -32768 a 32767
// = - operador de asignación
int red_on = 3000;
int red_yellow_on = 1000;
int green_on = 3000;
int green_blink = 500;
int yellow_on = 1000;

void setup() {
  // puertos a los que están conectados los LED - salidas
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

}

void loop() {
  //enciende el voltaje en la salida RED_PIN (el rojo está conectado allí)
  digitalWrite(RED_PIN, HIGH);
  //esperando hasta que se encienda el rojo
  delay(red_on);
  //encienda el voltaje en la salida YELLOW_PIN (amarillo)
  digitalWrite(YELLOW_PIN, HIGH);
  delay(red_yellow_on);
  
  //desactivar RED_PIN y YELLOW_PIN, activar GREEN_PIN (verde)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(green_on);
  digitalWrite(GREEN_PIN, LOW);
  
  //encender y apagar el verde tres veces
  delay(green_blink);
  digitalWrite(GREEN_PIN, HIGH);
  delay(green_blink);
  digitalWrite(GREEN_PIN, LOW);
  delay(green_blink);
  digitalWrite(GREEN_PIN, HIGH);
  delay(green_blink);
  digitalWrite(GREEN_PIN, LOW);
  delay(green_blink);
  digitalWrite(GREEN_PIN, HIGH);
  delay(green_blink);
  digitalWrite(GREEN_PIN, LOW);
  
  //amarillo solo
  digitalWrite(YELLOW_PIN, HIGH);
  delay(yellow_on);
  digitalWrite(YELLOW_PIN, LOW); 

}
