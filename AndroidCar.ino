#include <SoftwareSerial.h>

//PWM
#define Lpwm_pin  5     //adjusting speed  
#define Rpwm_pin  10    //adjusting speed  //
unsigned char Lpwm_val = 150;
unsigned char Rpwm_val = 150;

//Pines Salida
int pinLB=2;    // defining pin2 left Tracero
int pinLF=4;    // defining pin4 left Delantero
int pinRB=7;    // defining pin7 right Tracero
int pinRF=8;    // defining pin8 right Delantero

//Variables
int currentByte = 0;
int prevByte; 

//Bluetooth
int rxBluetooth = 2;
int txBluetooth = 3; 
SoftwareSerial ble(rxBluetooth, txBluetooth); // RX, TX

//Funciones de Motor
void pinesConfiugracion(void)
{
  pinMode(pinLB,OUTPUT); 
  pinMode(pinLF,OUTPUT); 
  pinMode(pinRB,OUTPUT); 
  pinMode(pinRF,OUTPUT); 
  pinMode(Lpwm_pin,OUTPUT); 
  pinMode(Rpwm_pin,OUTPUT);
  analogWrite(Lpwm_pin,Lpwm_val);
  analogWrite(Rpwm_pin,Rpwm_val);
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
            Serial.print("R <= 100\r\n");
        }
        if (currentByte > 100)
        {
            digitalWrite(pinRF, HIGH);
            digitalWrite(pinRB, LOW);
            Serial.print("R > 100\r\n");
        }
    }

    //Motores Left
    if (prevByte == 203)
    {
        if (currentByte <= 100)
        {
            digitalWrite(pinLB, HIGH);
            digitalWrite(pinLF, LOW);
            Serial.print("L <= 100\r\n");
        }

        if (currentByte > 100)
        {
            digitalWrite(pinLF, HIGH);
            digitalWrite(pinLB, LOW);
            Serial.print("R > 100\r\n");
        }
    }

    //stop
    if (prevByte == 213 && currentByte == 99)
    {
        stopp();
        Serial.print("STOP\r\n");
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
   Serial.print("Configuro Bluetooth\r\n");
   ble.begin(9600);
   Serial.print("Stop\r\n");
   stopp(); 
}
void loop()
{
    if (ble.available() > 0)
    {
        currentByte = ble.read();
        output_sets();
        prevByte = currentByte;
    }
}



