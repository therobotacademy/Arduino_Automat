/***   Global variables   ***/
int P_VERDE_PIN=12;

/***   Function declaration   ***/

void setup()
{



}


void loop()
{
    pinMode(P_VERDE_PIN,OUTPUT);
    digitalWrite(P_VERDE_PIN,HIGH);
    delay(400);
    pinMode(P_VERDE_PIN,OUTPUT);
    digitalWrite(P_VERDE_PIN,LOW);
    delay(400);

}

/***   Function definition   ***/
