

/*
  capteurQ

  Copyright (c) 2017 IOT-4DL
  Licensed under the MIT license.

  */

  /* 
   * HC-05 will be paired with default PIN : 1234
   */

// includes
//#include <dht.h>
#include <DHT.h>              //install dht.h and dht.cpp as library (in zip format)
#include <SoftwareSerial.h>

// defines
#define DHT11_PIN 5
//#define DHT22_PIN 5
#define rxPin 13           //for D10
#define txPin 14           //for D11

//dht DHT;
SoftwareSerial mySerial(rxPin, txPin); 
char myChar ; 

// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(9600);   
  Serial.println("Serial ...");
  mySerial.begin(9600);
  mySerial.println("Software Serial...");
}

// the loop function runs over and over again forever
void loop() 
{
  while(mySerial.available())
  {
    myChar = mySerial.read();
    Serial.print(myChar);
  }

  while(Serial.available())
  {
    myChar = Serial.read();
    mySerial.print(myChar);
  }

}
