/// Variables //////////////////////////////////////////////////////////////////////////////////////////////////////////////
int encoder_pin = 2;            //Pin 2, donde se conecta el encoder     
int encoder_pin_A = A5;            //Pin A5, donde se conecta la señal analógica del encoder  
float rpm = 0;           // Revoluciones por minuto calculadas.
float velocity = 0;                 //Velocidad en [Km/h]
volatile byte pulses = 0;       // Número de pulsos leidos por el Arduino en un segundo
unsigned long timeold = 0;  // Tiempo 
unsigned int pulsesperturn = 1; //20; // Número de muescas que tiene el disco del encoder.
const int wheel_diameter = 65;   // Diámetro de la rueda pequeña[mm]
static volatile unsigned long debounce = 0; // Tiempo del rebote.
////  Configuración del Arduino /////////////////////////////////////////////////////////
void setup(){
   Serial.begin(9600); // Configuración del puerto serie  
   pinMode(encoder_pin, INPUT); // Configuración del pin nº2
   attachInterrupt(0, counter, RISING); // Configuración de la interrupción 0, donde esta conectado. 
   pulses = 0;
   rpm = 0;
   timeold = 0;
}
////  Programa principal ///////////////////////////////////////////////////////////////////////
 void loop(){
  /*/ Serial Plotter: graph of digital and analog signal
  Serial.print(digitalRead(encoder_pin)*500); Serial.print("\t");
  Serial.print(300,DEC);  Serial.print("\t");
  Serial.print(600,DEC);  Serial.print("\t");
  Serial.println(analogRead(encoder_pin_A));
  */
  
  if (millis() - timeold >= 1000) {
    // Se actualiza cada segundo
    noInterrupts(); //Don't process interrupts during calculations // Desconectamos la interrupción para que no actué en esta parte del programa.
      rpm = 60*((float)pulses/(float)pulsesperturn)/ ((millis() - timeold)/1000); // Calculamos las revoluciones por minuto
      velocity = rpm * 3.1416 * wheel_diameter * 60 / 1000000; // Cálculo de la velocidad en [Km/h] 
      
    timeold = millis(); // Almacenamos el tiempo actual.
    Serial.print("Seconds "); Serial.print(millis()/1000); Serial.print("\t");// Se envia al puerto serie el valor de tiempo, de las rpm y los pulsos.
    Serial.print("RPM ");     Serial.print(rpm,2);         Serial.print("\t");
    Serial.print("Pulses ");  Serial.print(pulses,DEC);    Serial.print("\t"); 
    Serial.print("Velocity[Km/h]"); Serial.println(velocity,2); 
    pulses = 0;  // Inicializamos los pulsos.
    interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
  }
 }
////Fin de programa principal //////////////////////////////////////////////////////////////////////////////////
///////////////////////////Función que cuenta los pulsos buenos ///////////////////////////////////////////
 void counter(){
  if(  digitalRead(encoder_pin) && (micros()-debounce > 500) && digitalRead(encoder_pin) ) { 
// Vuelve a comprobar que el encoder envia una señal buena y luego comprueba que el tiempo es superior a 500 microsegundos y vuelve a comprobar que la señal es correcta.
        debounce = micros(); // Almacena el tiempo para comprobar que no contamos el rebote que hay en la señal.
        pulses++;}  // Suma el pulso bueno que entra.
        else ; } 
