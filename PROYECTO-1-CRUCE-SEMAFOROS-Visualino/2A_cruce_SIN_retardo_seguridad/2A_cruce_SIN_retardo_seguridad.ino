/***   Global variables   ***/
int estado=1;
int P_ROJO_PIN=8;
int P_AMARILLO_PIN=10;
int P_VERDE_PIN=12;
int S_ROJO_PIN=2;
int S_AMARILLO_PIN=4;
int S_VERDE_PIN=6;
int E1=4500;
int E2=1500;
int E3=2500;
int E4=2500;

/***   Function declaration   ***/
void ciclo_semaforo (String semaforo, int rojo, int amarillo, int verde);

void setup()
{












}


void loop()
{
    switch (estado)
    {
      case 1:
      {
        ciclo_semaforo("principal", 0, 0, 1);
        ciclo_semaforo("secundario", 1, 0, 0);
        delay(E1);
        break;
      }
      case 2:
      {
        ciclo_semaforo("principal", 0, 1, 0);
        ciclo_semaforo("secundario", 1, 0, 0);
        delay(E2);
        break;
      }
      case 3:
      {
        ciclo_semaforo("principal", 1, 0, 0);
        ciclo_semaforo("secundario", 0, 0, 1);
        delay(E3);
        break;
      }
      case 4:
      {
        ciclo_semaforo("principal", 1, 0, 0);
        ciclo_semaforo("secundario", 0, 1, 0);
        delay(E4);
        break;
      }
      default:
      {
        estado=1;
      }
    }
    estado=estado + 1;
    if (estado > 4) {
      estado=1;
     }

}

/***   Function definition   ***/
void ciclo_semaforo (String semaforo, int rojo, int amarillo, int verde) {
  if (semaforo == "principal") {
    if (rojo == 1) {
      pinMode(P_ROJO_PIN,OUTPUT);
      digitalWrite(P_ROJO_PIN,HIGH);
     }else {
      pinMode(P_ROJO_PIN,OUTPUT);
      digitalWrite(P_ROJO_PIN,LOW);
     }
    if (amarillo == 1) {
      pinMode(P_AMARILLO_PIN,OUTPUT);
      digitalWrite(P_AMARILLO_PIN,HIGH);
     }else {
      pinMode(P_AMARILLO_PIN,OUTPUT);
      digitalWrite(P_AMARILLO_PIN,LOW);
     }
    if (verde == 1) {
      pinMode(P_VERDE_PIN,OUTPUT);
      digitalWrite(P_VERDE_PIN,HIGH);
     }else {
      pinMode(P_VERDE_PIN,OUTPUT);
      digitalWrite(P_VERDE_PIN,LOW);
     }
   }
  if (semaforo == "secundario") {
    if (rojo == 1) {
      pinMode(S_ROJO_PIN,OUTPUT);
      digitalWrite(S_ROJO_PIN,HIGH);
     }else {
      pinMode(S_ROJO_PIN,OUTPUT);
      digitalWrite(S_ROJO_PIN,LOW);
     }
    if (amarillo == 1) {
      pinMode(S_AMARILLO_PIN,OUTPUT);
      digitalWrite(S_AMARILLO_PIN,HIGH);
     }else {
      pinMode(S_AMARILLO_PIN,OUTPUT);
      digitalWrite(S_AMARILLO_PIN,LOW);
     }
    if (verde == 1) {
      pinMode(S_VERDE_PIN,OUTPUT);
      digitalWrite(S_VERDE_PIN,HIGH);
     }else {
      pinMode(S_VERDE_PIN,OUTPUT);
      digitalWrite(S_VERDE_PIN,LOW);
     }
   }
 }
