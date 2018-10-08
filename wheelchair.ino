#include<SPI.h>
#include<RF24.h>
#include<nRF24L01.h>
#include "printf.h"
//receiver
//NRF      ARDUINO
//1 GND    GND
//2 VCC    3.3V
//3 CE     9  out
//4 CSN    10  out
//5 SCK    13 out
//6 MOSI   11 out
//7 MISO   12 in

//int radio_led = 13;
int CE_PIN = 7, CSN_PIN = 8;
RF24 Radio(CE_PIN, CSN_PIN);
const uint64_t pipeIn = 0xD4D4F0F0E1LL;

struct radio
{
  int x1;
} data;
//const int xpin = A0;                  // x-axis of the accelerometer
//const int ypin = A1;                  // y-axis
//const int zpin = A2;                  // z-axis (only on 3-axis models)


void setup()
{
  Serial.begin(9600);
  //pinMode(radio_led, OUTPUT);
  Radio.begin();
  printf_begin();
  Radio.setPALevel(RF24_PA_MIN);
  Radio.setDataRate(RF24_250KBPS);
  Radio.openReadingPipe(0, pipeIn);
  Radio.startListening();
  Radio.printDetails();
  delay(2000);
  data.x1 = 0;
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  
}

void loop()
{
//  int x = analogRead(xpin);  //read from xpin 
 //int y = analogRead(ypin);  //read from ypin
 
// int z = analogRead(zpin);  //read from zpin

 //x=map(x,349,281,0,90);
// y=map(y,200,280,0,90);
// z=map(z,425,357,0,90);
//Serial.print(x); 
//Serial.print("\t");
//Serial.print(y);
//Serial.print("\t");
//Serial.print(z);
//Serial.print("\n");

if (Radio.available())
  {
    Radio.read(&data, sizeof(data));
   // digitalWrite(radio_led, HIGH);
  }
  else
  {
//    digitalWrite(radio_led, LOW);
  }
  Serial.print(data.x1);
  Serial.print("   ");
  int x1=data.x1;
/*int x2=0;
if((y>=40 && y<=55))
x2=2;
else if(y>=55)
x2=3;
else if(y<40)
x2=1;*/
 if(x1==1)
 {
  forward(180);
 }
 else if(x1==2)
 left(180);
 else if(x1==3)
 right(180);
 else if(x1==4)
 stop1();
} 
void forward(int n)
{
  Serial.println("FORWARD");
  analogWrite(3,n);
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,n);
}

void left(int n)
{
  Serial.println("LEFT");
  analogWrite(3,n-80);
  analogWrite(5,0);
  analogWrite(9,0);
  analogWrite(6,n);
}

void right(int n)
{
  Serial.println("RIGHT");
  analogWrite(3,n);
  analogWrite(5,0);
  analogWrite(6,(n-80));
  analogWrite(9,0);
}

void stop1()
{
  Serial.println("STOP");
  analogWrite(3,0);
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,0);
}
