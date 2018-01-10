int pushButton = 12;
int pushButton_Analog = A5;
int led = 13; // LED interno de la placa LED_BUILTIN

int buttonState = 0;  // Estado del pulsador
int buttonAnalog = 0;  // Lectura analógica del pulsador

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  buttonState = digitalRead(pushButton);
  buttonAnalog = analogRead(pushButton_Analog);
  Serial.println(buttonState);
  delay(1);

  if (buttonState == LOW) {
    digitalWrite(led, LOW);
    Serial.print("Apago Led con valor analógico ");
  }
  else {
    digitalWrite(led, HIGH);
    Serial.print("Enciendo Led con valor analógico ");
  }
  Serial.println(buttonAnalog/1023*5);
}
