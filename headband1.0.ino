#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include<SPI.h>
#include<RF24.h>
#include<nRF24L01.h>
#include "printf.h"

//NRF      ARDUINO
//1 GND    GND
//2 VCC    3.3V
//3 CE     9  out
//4 CSN    10  out
//5 SCK    13 out
//6 MOSI   11 out
//7 MISO   12 in

int CE_PIN = 7, CSN_PIN = 8;
RF24 Radio(CE_PIN, CSN_PIN);
const uint64_t pipeOut = 0xD4D4F0F0E1LL;

struct radio
{
  int x;
} data;

const int xpin = A1;                  // x-axis of the accelerometer
const int ypin = A0;                  // y-axis
//const int zpin = A5;                  // z-axis (only on 3-axis models)

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
Radio.begin();
  printf_begin();
  Radio.setPALevel(RF24_PA_MAX);
  Radio.setDataRate(RF24_250KBPS);
  Radio.openWritingPipe(pipeOut);
  Radio.printDetails();
  delay(2000);
  data.x = 1;
  int counter=1,c=0; 
  int  countr=0;
}

void loop() {
  int x = analogRead(xpin);  //read from xpin
 
 int y = analogRead(ypin);  //read from ypin
 
 //int z = analogRead(zpin);  //read from zpin
int x1_=0;
 x=map(x,267,403,-90,90);
 y=map(y,275,400,-90,90);
 //z=map(z,270,350,-90,90);
Serial.print(x); 
Serial.print("\t");
Serial.print(y);
Serial.print("\t");
//Serial.print(z);  
Serial.print("\n");

if(counter==3)
{
  Serial.print("Perstop");
  x1_=4;
  stop1();
 
  if((x>=-20 && x<=10)&&(y>=-90 && y<=-40)/*&&(z>=-80 && z<=-25)*/)
 {x1_=4; Serial.print("stop");
 countr++;
 c=1;}
 else
 {
  if(c==1)
  counter++;
  c=0;
 }
}
else
{
 if((x>=-20 && x<=10)&&(y>=-90 && y<=-40)/*&&(z>=-80 && z<=-25)*/)
 {x1_=4; Serial.print("stop");
 counter++;
 c=1;}
else if((x>=(-15) && x<=20)&&(y>=(60) && y<=(95))/*&&(z>=(-40) && z<=-5)*/)
{
   Serial.print("Forward");
 counter=0;
  x1_=1;
  c=0;
}
else if((x>=35 && x<=70)&&(y>=0 && y<=60)/*&&(z>=-65 && z<=-25)*/)
{ x1_=2; 
counter=0;c=0;
Serial.print("left");} 
 else if((x>=-75 && x<=-30)&&(y>=5 && y<=60)/*&&(z>=-80 && z<=-10)*/)
{ 
  x1_=3; 
  counter=0;c=0;
  Serial.print("right");}
 else
 {
  if(c==1)
  counter++;
  c=0;
 }
}
data.x=x1_;
 Serial.print(x1_);
 Serial.print("\n");
Radio.write(&data, sizeof(data));
delay(1000); 
  // put your main code here, to run repeatedly:
}
