/* Knight Rider 2
   --------------

   Reducing the amount of code using for(;;).


   (cleft) 2005 K3, Malmo University
   @author: David Cuartielles
   @hardware: David Cuartielles, Aaron Hallborg
   @modified by: aprendiendoarduino
*/

int pinArray[] = {3, 5, 8, 10, 12};
int count = 0;
int timer = 400;

void setup() {
  Serial.begin(9600);
  // we make all the declarations at once
  for (count = 0; count < 5; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  timer = analogRead(A0)/4;	//El valor leido por analog read es el temporizador
  Serial.print("timer= ");
  Serial.println(timer);
  for (count = 0; count < 5; count++) {
    //timer = analogRead(A0);
    digitalWrite(pinArray[count], HIGH);
    Serial.print("Enciendo led ");
    Serial.println(pinArray[count]);
    delay(timer);
    digitalWrite(pinArray[count], LOW);
    delay(timer);
  }
  for (count = 4; count >= 0; count--) {
    //timer = analogRead(A0);
    digitalWrite(pinArray[count], HIGH);
    Serial.print("Enciendo led ");
    Serial.println(pinArray[count]);
    delay(timer);
    digitalWrite(pinArray[count], LOW);
    delay(timer);
  }
}
