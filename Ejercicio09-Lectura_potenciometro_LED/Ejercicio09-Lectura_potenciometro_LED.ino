/*
Lectura de potenciómetro
*/
const int pin_led = 10;  // led conectado al pin 10 PWM
const int pin_pot = A1; // el pot esta conectado al pin A1

int pot = 0; // Entero porque es salida analógica
float volt = 0; // Float porque hay decimales en la operación
int brillo;  //variable para el brillo

void setup() {
   Serial.begin(9600);
   pinMode (pin_led, OUTPUT);  // declaramos el led como salida
}

void loop() {
    pot = analogRead(pin_pot);
    volt = (float)pot/1023*5; // Conversión a voltios
    Serial.print(pot);
    Serial.print(" corresponde a Voltios ");
    Serial.println(volt);
    
    brillo = (float)pot/1023*255; // Conversión a escala de 8 bits (PWM OUTPUT 0-255)
                                  //Entrada analógica en Arduino es de 10 bits (0-1023) 
    analogWrite(pin_led, brillo);
    
    delay(100);
}
