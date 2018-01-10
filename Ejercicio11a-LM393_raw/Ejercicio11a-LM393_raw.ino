/// Variables //////////////////////////////////////////////////////////////////////////////////////////////////////////////
int encoder_pin_D = 2;             //Pin 2 Digital, donde se conecta el encoder
int encoder_pin_A = A5;             //Pin 5 Analógico, donde se conecta el encoder

////  Configuración del Arduino /////////////////////////////////////////////////////////
void setup(){
   Serial.begin(9600); // Configuración del puerto serie  
   pinMode(encoder_pin_D, INPUT); // Configuración del pin nº2
  }

////  Programa principal ///////////////////////////////////////////////////////////////////////
void loop(){
  int D = 500*digitalRead(encoder_pin_D); // Escalamos para que los pulsos estén a mitad de la escala del rango de lectura analógico (0-1023)
  Serial.print(D); Serial.print("\t");
  float A = analogRead(encoder_pin_A);
  Serial.println(A);
  }

