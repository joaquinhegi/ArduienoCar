#include <SoftwareSerial.h>

SoftwareSerial BT1(9, 6);// RX, TX

//PWM
#define Lpwm_pin 10     //adjusting speed  
#define Rpwm_pin 5    //adjusting speed  //
unsigned char Lpwm_val = 130;
unsigned char Rpwm_val = 130;

//Pines Salida
int pinLB=7;    // defining pin2 left Tracero
int pinLF=8;    // defining pin4 left Delantero
int pinRB=2;    // defining pin7 right Tracero
int pinRF=4;    // defining pin8 right Delantero

//Variables
int currentByte = 0;
int prevByte = 0; 



//Funciones de Motor
void pinesConfiugracion(void)
{
  pinMode(pinLB,OUTPUT); 
  pinMode(pinLF,OUTPUT); 
  pinMode(pinRB,OUTPUT); 
  pinMode(pinRF,OUTPUT); 
  pinMode(Lpwm_pin,OUTPUT); 
  pinMode(Rpwm_pin,OUTPUT);
}

void output_sets()
{
    //Motores Right
    if (prevByte == 202)
    {
        if (currentByte <= 100)
        {
            digitalWrite(pinRB, HIGH);
            digitalWrite(pinRF, LOW);
            //
            int aux = (currentByte)*2.35;
            if(aux > Rpwm_val)
               aux = Rpwm_val;
            analogWrite(Rpwm_pin,aux);
            //
            Serial.println("R <= 100" );
        }
        if (currentByte > 100)
        {
            digitalWrite(pinRF, HIGH);
            digitalWrite(pinRB, LOW);
            //
            int aux = (currentByte-100)*2.35;
            if(aux > Rpwm_val)
               aux = Rpwm_val;
            analogWrite(Rpwm_pin,aux);
            //
            Serial.println("R > 100");
        }
    }

    //Motores Left
    if (prevByte == 203)
    {
        if (currentByte <= 100)
        {
            digitalWrite(pinLB, HIGH);
            digitalWrite(pinLF, LOW);
            //
            int aux = (currentByte)*2.35;
            if(aux > Rpwm_val)
               aux = Rpwm_val;
            analogWrite(Lpwm_pin,aux); 
            //   
            Serial.println("L <= 100");
        }

        if (currentByte > 100)
        {
            digitalWrite(pinLF, HIGH);
            digitalWrite(pinLB, LOW);
            //
            int aux = (currentByte-199)*2.35;
            if(aux > Rpwm_val)
               aux = Rpwm_val;
            analogWrite(Lpwm_pin,aux);
            //
            Serial.println("L > 100");
        }
    }

    //stop
    if (prevByte == 213 && currentByte == 99)
    {
        stopp();
        Serial.println("STOP");
    }
} 

void stopp() //stop
{
    digitalWrite(pinRB, HIGH);
    digitalWrite(pinRF, HIGH);
    digitalWrite(pinLB, HIGH);
    digitalWrite(pinLF, HIGH);
}

//Funciones Principales
void setup() 
{ 
   pinesConfiugracion();
   Serial.begin(9600);
   Serial.println("Configuro Bluetooth");
   BT1.begin(9600);
   Serial.println("Stop");
   stopp();
   
}
void loop()
{

    if (BT1.available())
    {
        currentByte = BT1.read();
        //Serial.println(currentByte);  
        output_sets();
        prevByte = currentByte;
       // Serial.print(prevByte);
    }
}



