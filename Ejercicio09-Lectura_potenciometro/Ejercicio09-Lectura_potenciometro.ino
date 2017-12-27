/*
Lectura de potenciómetro
*/

int pot = 0; // Entero porque es salida analógica
float volt = 0; // Float porque hay decimales en la operación

void setup() {
   Serial.begin(9600); 
}

void loop() {
    pot = analogRead(A0);
    volt = (float)pot/1023*5; // Conversión a voltios
    Serial.print(pot);
    Serial.print(" corresponde a Voltios ");
    Serial.println(volt);
    delay(100);
}
