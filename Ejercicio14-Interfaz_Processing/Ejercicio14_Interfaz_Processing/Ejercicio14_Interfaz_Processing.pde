/*
  theRobotAcademy.com
  by B. Ronquillo
  Arduino + Processing: Primeros Pasos
*/
 
import processing.serial.*; //Importamos la librería Serial
 
Serial port; //Nombre del puerto serie
 
PrintWriter output;  //Para crear el archivo de texto donde guardar los datos
 
int rquad=40; //Radio del quadrado
int xquad=200;  //Posición X de rect
int yquad=200;  //Posición Y de rect
boolean overRect = false; //Estado del mouse si está encima de rect o no
 
//Colores del botón
int red=255;
int green=100;
int blue=100;
 
boolean status=false; //Estado del color de rect
String texto="LED OFF";//Texto del status inicial del LED
 
int xlogo=400;//Posición X de la imagen
int ylogo=50;//Posición Y de la imagen
 
int valor;//Valor de la temperatura
 
//Colores esfera temperatura
float rojo;
float verde;
float azul;
 
void setup()
{
  println(Serial.list()); //Visualiza los puertos serie disponibles en la consola de abajo
  int port_index = 0; // Indice del puerto seleccionado
  port = new Serial(this, Serial.list()[port_index], 9600); //Abre el puerto serie COM4
  print(port.list()[port_index]);
   
  output = createWriter("temperatura_datos.txt"); //Creamos el archivo de texto, que es guardado en la carpeta del programa
   
  size(800, 400); //Creamos una ventana de 800 píxeles de anchura por 600 píxeles de altura 
}
 
void draw()
{
  background(255,255,255);//Fondo de color blanco
    
  if(mouseX > xquad-rquad && mouseX < xquad+rquad &&  //Si el mouse se encuentra dentro de rect
     mouseY > yquad-rquad && mouseY < yquad+rquad)
     {
       overRect=true;  //Variable que demuestra que el mouse esta dentro de rect
       stroke(255,0,0);  //Contorno de rect rojo
     }
   else
   {
     overRect=false;  //Si el mouse no está dentro de rect, la variable pasa a ser falsa
     stroke(0,0,0);  //Contorno de rect negro
   }
   
  //Dibujamos un rectangulo de color gris
  fill(red,green,blue);
  rectMode(RADIUS); //Esta función hace que Width y Height de rect sea el radio (distancia desde el centro hasta un costado).
  rect(xquad,yquad,rquad,rquad);
   
  //Creamos un texto de color negro con la palabra LED
  fill(0,0,0);
  PFont f = loadFont("Calibri-48.vlw");//Tipo de fuente
  textFont(f, 20);
  text(texto, 170, 270);
   
  //Ponemos la imagen de nuestro logo
  imageMode(CENTER);//Esta función hace que las coordenadas de la imagne sean el centro de esta y no la esquina izquierda arriba
  PImage imagen=loadImage("logo.png");
  image(imagen,xlogo,ylogo,400,100);
 
  //Recibir datos temperatura del Arduino 
  if(port.available() > 0) // si hay algún dato disponible en el puerto
   {
     valor=port.read();//Lee el dato y lo almacena en la variable "valor"
   }
   //Visualizamos la temperatura con un texto
   text("Temperatura =",390,200);
   text(valor, 520, 200);
   text("ºC",547,200);
    
   //Escribimos los datos de la temperatura con el tiempo (h/m/s) en el archivo de texto
   output.print(valor + " ºC     ");
   output.print(hour( )+":");
   output.print(minute( )+":");
   output.println(second( ));
   output.println("");
    
  //Esfera color visualización temperatura
  float temp = map (valor, 15,32, 0, 255);//Escalamos la temperatura donde maximo sea 32ºC y mínimo 15ºC
  rojo=temp;
  verde=temp*-1 + 255;
  azul=temp*-1 + 255;
  //Dibujamos una esfera para colorear la temperatura
  noStroke();
  fill(rojo,verde,azul);
  ellipseMode(CENTER);
  ellipse(590,193,20,20);
}
 
void mousePressed()  //Cuando el mouse está apretado
{
  if (overRect==true) //Si el mouse está dentro de rect
  {
    status=!status; //El estado del color cambia
    port.write("A"); //Envia una "A" para que el Arduino encienda el led
    if(status==true)
    {
      //Color del botón rojo
      red=255;
      green=0;
      blue=0;
      texto="LED ON";
    }
    if(status==false)
    {
      //Color del botón negro
      red=100;
      green=100;
      blue=100;
      texto="LED OFF";
    }
  }
}
 
void keyPressed() //Cuando se pulsa una tecla
{
  if(key=='w'||key=='W')
  {
        ylogo--; //El logo se deplaza hacia arriba
  }
  else if(key=='s'||key=='S')
  {
        ylogo++; //El logo se deplaza hacia abajo
  }
  else if(key=='a'||key=='A')
  {
        xlogo--; //El logo se desplaza hacia la izquierda
  }
  else if(key=='d'||key=='D')
  {
        xlogo++; //El logo se desplaca hacia la derecha
  }
  //Pulsar la tecla E para salir del programa
  if(key=='e' || key=='E')
  {
    output.flush(); // Escribe los datos restantes en el archivo
    output.close(); // Final del archivo
    exit();//Salimos del programa
  }
}