/*
  Interactivo
*/
#define DEBUG 0

String leido = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Introduce una cadena de texto: ");
  while (Serial.available() == 0) {
    //No hago nada
  }

  do {
    char caracter_leido;
    delay(5);
    caracter_leido = Serial.read();
    if (1){
    Serial.print("Caracter leido: ");
    Serial.print(caracter_leido);
    Serial.print(" --> ");
    Serial.println(caracter_leido, DEC);
    Serial.print("Caracteres en buffer: ");
    Serial.println(Serial.available());
    Serial.println();
    }
    leido += caracter_leido;
  }  while (Serial.available() > 0);

  Serial.println("He leido la cadena: \"" + leido + "\"");
}

void loop() {

  //no hago nada

}

