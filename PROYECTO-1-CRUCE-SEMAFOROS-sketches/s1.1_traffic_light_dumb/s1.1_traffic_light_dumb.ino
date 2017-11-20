void setup() {
  //puertos a los que se conectan los LED - salidas
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {
  //encienda el voltaje en la octava salida (el rojo está conectado allí)
  digitalWrite(8, HIGH);
  //esperando hasta que se encienda el amarillo
  delay(3000);
  //encender el voltaje en la salida 10 (amarillo)
  digitalWrite(10, HIGH);
  delay(1000);
  
  //apague 8 y 10, encienda 12 (verde)
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, HIGH);
  delay(3000);
  digitalWrite(12, LOW);
  
  //encender y apagar el verde tres veces
  delay(500);
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  
  //amarillo solo
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW); 

}
