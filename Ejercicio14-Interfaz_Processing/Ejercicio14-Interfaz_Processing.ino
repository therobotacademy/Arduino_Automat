/*
  theRobotAcademy.com
  by B. Ronquillo
  Arduino + Processing: Primeros Pasos
*/

#include <OneWire.h>                 //Se importan las librerías
#include <DallasTemperature.h>
#define Pin_temp  2                  //Se declara el pin donde se conectará el sensor de temperatura DS18B20
#define Pin_led   11                  // Pin del LED

int temp;// Variable sensor de temperaura
boolean status=LOW; //Estado del led

OneWire ourWire(Pin_temp);           //Se establece el pin declarado como bus para la comunicación OneWire
DallasTemperature sensors(&ourWire); //Se llama a la librería DallasTemperature

void setup()
{
  delay(1000);
  sensors.begin(); //Se inician los sensores
  pinMode(Pin_led,OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{
  sensors.requestTemperatures();       //Prepara el sensor para la lectura
  temp = sensors.getTempCByIndex(0);
  Serial.write(int(temp));  // Para poder visualizar en la consola de PROCESSING
  /*
  byte * b = (byte *) &temp;
  Serial.write(b,4); // Para que pueda leerse desde processing
  */
  //Serial.print(temp); // Para poder visualizar en la consola de ARDUINO
  //Serial.println(" Grados Centigrados");
  
  delay(1000);                         //Se provoca una parada de 1 segundo antes de la próxima lectura
 
  /* ALTERNATIVA CON SENSOR DE TEMPERATURA ANALÓGICO LM35
  temp = analogRead(A0); //Lee los datos del sensor LM35
  temp = (5.0 * temp * 100)/1023.0;//Formula para convertir a ºC
  Serial.write(temp); //Enviamos los datos en forma de byte
  delay(100);
  */
 
  if(Serial.available()>0)//Si el Arduino recibe datos a través del puerto serie
  {
    byte dato = Serial.read(); //Los almacena en la variable "dato"
    if(dato==65)  //Si recibe una "A" (en ASCII "65")
    {
      status=!status; //Cambia el estatus del led
    }
    digitalWrite(Pin_led,status);
  }
}
