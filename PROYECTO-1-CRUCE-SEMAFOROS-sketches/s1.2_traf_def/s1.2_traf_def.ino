// definiciones de constantes para números de puerto, a los cuales se conectan los LED
// antes de la compilación, todo RED_PIN será reemplazado por 8, etc.
#define RED_PIN 8
#define YELLOW_PIN 10
#define GREEN_PIN 12

void setup() {
  //puertos a los que se conectan los LED - salidas
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

}

void loop() {
  //enciende la tensión en la salida RED_PIN (el rojo está conectado allí)
  digitalWrite(RED_PIN, HIGH);
  //esperando hasta que se encienda el rojo
  delay(3000);
  //encienda el voltaje en la salida YELLOW_PIN (amarillo)
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  
  //desactivar RED_PIN y YELLOW_PIN, activar GREEN_PIN (verde)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  delay(3000);
  digitalWrite(GREEN_PIN, LOW);
  
  //encender y apagar el verde tres veces
  delay(500);
  digitalWrite(GREEN_PIN, HIGH);
  delay(500);
  digitalWrite(GREEN_PIN, LOW);
  delay(500);
  digitalWrite(GREEN_PIN, HIGH);
  delay(500);
  digitalWrite(GREEN_PIN, LOW);
  delay(500);
  digitalWrite(GREEN_PIN, HIGH);
  delay(500);
  digitalWrite(GREEN_PIN, LOW);
  
  //amarillo solo	
  digitalWrite(YELLOW_PIN, HIGH);
  delay(1000);
  digitalWrite(YELLOW_PIN, LOW); 

}
