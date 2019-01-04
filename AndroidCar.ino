

#include <SoftwareSerial.h>
SoftwareSerial ble(2, 3); // RX, TX

#define Lpwm_pin  5     //adjusting speed  
#define Rpwm_pin  10    //adjusting speed  //
int pinLB=2;     // defining pin2 left rear
int pinLF=4;     // defining pin4 left front
int pinRB=7;    // defining pin7 right rear
int pinRF=8;    // defining pin8 right front
unsigned char Lpwm_val = 150;
unsigned char Rpwm_val = 150;
int Car_state=0;
int current_byte = 0;
int prev_byte; 

//Funciones de Motor
void M_Control_IO_config(void)
{
  pinMode(pinLB,OUTPUT); // pin 2
  pinMode(pinLF,OUTPUT); // pin 4
  pinMode(pinRB,OUTPUT); // pin 7 
  pinMode(pinRF,OUTPUT); // pin 8
  pinMode(Lpwm_pin,OUTPUT); // pin 11 (PWM) 
  pinMode(Rpwm_pin,OUTPUT); // pin 10 (PWM)   
}
void Set_Speed(unsigned char Left,unsigned char Right)
{
  analogWrite(Lpwm_pin,Left);
  analogWrite(Rpwm_pin,Right);
}

//Funciones Principales
void setup() 
{ 
   M_Control_IO_config();
   Set_Speed(Lpwm_val,Rpwm_val);
   Serial.begin(9600);   //initialized serial port , using Bluetooth as serial port, setting baud at 9600 
   ble.begin(9600);
   stopp(); 
}
void loop()
{
    if (ble.available() > 0)
    {
        current_byte = ble.read();
        outputs_set();
        prev_byte = current_byte;
    }
}

void output_sets()
{
    //Motores Right
    if (prev_byte == 202)
    {
        if (current_byte <= 100)
        {
            digitalWrite(pinRB, HIGH);
            digitalWrite(pinRF, LOW);
            Serial.print("R <= 100")
        }
        if (current_byte > 100)
        {
            digitalWrite(pinRF, HIGH);
            digitalWrite(pinRB, LOW);
            Serial.print("R > 100")
        }
    }

    //Motores Left
    if (prev_byte == 203)
    {
        if (current_byte <= 100)
        {
            digitalWrite(pinLB, HIGH);
            digitalWrite(pinLF, LOW);
            Serial.print("L <= 100")
        }

        if (current_byte > 100)
        {
            digitalWrite(pinLF, HIGH);
            digitalWrite(pinLB, LOW);
            Serial.print("R > 100")
        }
    }

    //stop
    if (prev_byte == 213 && current_byte == 99)
    {
        stopp();
        Serial.print("STOP")
    }
} 

void stopp() //stop
{
    digitalWrite(pinRB, HIGH);
    digitalWrite(pinRF, HIGH);
    digitalWrite(pinLB, HIGH);
    digitalWrite(pinLF, HIGH);
    Car_state = 5;
}