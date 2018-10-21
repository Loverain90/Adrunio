#include <SPI.h>
#include "RF24.h"

/* 
 *  Nodemcu       NRF24L01
    D8 -----------> CE
    D3 -----------> CSN
    D5 -----------> SCK
    D6 -----------> MISO
    D7 -----------> MOSI
 */
 
const uint64_t pipe = 0xE8E8F0F0E1LL; // địa chỉ phát
RF24 radio(9,10);//setup pin, need to modify
byte msg[3];
const int led = D0;
int led_st = 0;
 
void setup(){
  Serial.begin(115200);
  radio.begin();                     
  radio.setAutoAck(1);              
  radio.setDataRate(RF24_1MBPS);    // Tốc độ dữ liệu
  radio.setChannel(10);               // Đặt kênh
  radio.openReadingPipe(1,pipe);     
  radio.startListening();            
  pinMode(led, OUTPUT);
}
 
void loop(){
  if (radio.available()){
    while (radio.available()){
      radio.read(&msg, sizeof(msg));
      Serial.println(msg[0]);
      analogWrite(led, msg[0]);
    }
  }
}
