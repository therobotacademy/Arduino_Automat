/* Knight Rider 1
 * --------------
 *
 * Basically an extension of Blink_LED.
 *
 *
 * (cleft) 2005 K3, Malmo University
 * @author: David Cuartielles
 * @hardware: David Cuartielles, Aaron Hallborg
 * modifed by: aprendiendoarduino
 */

int pin2 = 3;
int pin3 = 5;
int pin4 = 8;
int pin5 = 10;
int pin6 = 12;
int timer = 400;

void setup(){
  Serial.begin(9600);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
}

void loop() {

   timer = analogRead(A0)/4;	//El valor leido por analog read es el temporizador
   Serial.print("timer= ");
   Serial.println(timer);
   
   digitalWrite(pin2, HIGH);
   Serial.println("Enciendo primer led");
   delay(timer);
   digitalWrite(pin2, LOW);
   delay(timer);

   digitalWrite(pin3, HIGH);
   Serial.println("Enciendo segundo led");
   delay(timer);
   digitalWrite(pin3, LOW);
   delay(timer);

   digitalWrite(pin4, HIGH);
   Serial.println("Enciendo tercer led");
   delay(timer);
   digitalWrite(pin4, LOW);
   delay(timer);

   digitalWrite(pin5, HIGH);
   Serial.println("Enciendo cuarto led");
   delay(timer);
   digitalWrite(pin5, LOW);
   delay(timer);

   digitalWrite(pin6, HIGH);
   Serial.println("Enciendo quinto led");
   delay(timer);
   digitalWrite(pin6, LOW);
   delay(timer);

   digitalWrite(pin5, HIGH);
   Serial.println("Enciendo cuarto led");
   delay(timer);
   digitalWrite(pin5, LOW);
   delay(timer);

   digitalWrite(pin4, HIGH);
   Serial.println("Enciendo tercer led");
   delay(timer);
   digitalWrite(pin4, LOW);
   delay(timer);

   digitalWrite(pin3, HIGH);
   Serial.println("Enciendo segundo led");
   delay(timer);
   digitalWrite(pin3, LOW);
   delay(timer);
}
