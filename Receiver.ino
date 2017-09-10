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

int radio_led = 13;
int CE_PIN = 3, CSN_PIN = 4;
RF24 Radio(CE_PIN, CSN_PIN);
const uint64_t pipeIn = 0xB8B8F0F0E1LL;

struct radio
{
  int x;
  int y;
} data;

void setup()
{
  Serial.begin(9600);
  pinMode(radio_led, OUTPUT);
  Radio.begin();
  printf_begin();
  Radio.setPALevel(RF24_PA_MIN);
  Radio.setDataRate(RF24_250KBPS);
  Radio.openReadingPipe(0, pipeIn);
  Radio.startListening();
  Radio.printDetails();
  delay(2000);
  data.x = 0;
  data.y = 0;
}

void loop()
{
  if (Radio.available())
  {
    Radio.read(&data, sizeof(data));
    digitalWrite(radio_led, HIGH);
  }
  else
  {
    digitalWrite(radio_led, LOW);
  }
  Serial.print(data.x);
  Serial.print("   ");
  Serial.println(data.y);
}
