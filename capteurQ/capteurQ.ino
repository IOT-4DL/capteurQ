

/*
  capteurQ

  Copyright (c) 2017 IOT-4DL
  Licensed under the MIT license.

  */

  /* 
   * HC-05 will be paired with default PIN : 1234
   */

#include "DHT.h"
#include "DigitalPin.h"
// use software serial port to communicate with bluetooth module hc-05
#include "SoftwareSerial.h"
//#include <DHT.h>              //install dht.h and dht.cpp as library (in zip format)
//#include <SoftwareSerial.h>

// defines
#define DHTPIN 5     // what digital pin we're connected to
#define rxPin 10           //for D10 as TX on board
#define txPin 11           //for D11 as RX on board

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(rxPin, txPin); 
char myChar; 

int mq135value;


DigitalPin PowerLed(13, false, true); // initial state is off (false), invert true = high turns led off
DigitalPin greenLed(2, false, true);  // initial state is off (false), invert true = high turns led off
DigitalPin redLed(3, false, true);    // initial state is off (false), invert true = high turns led off

// the setup function runs once when you press reset or power on the board
void setup() {

  mySerial.begin(9600);
  mySerial.println("Software Serial...");
  Serial.begin(9600);
  Serial.println("CapteurQ init");
  dht.begin();
}

// the loop function runs over and over again forever
void loop() {
  //All words typed in the console will be send - This part is only needed to test data sending
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

  // Wait a few seconds between measurements.
  delay(5000);
  mq135value = analogRead(0);
  mySerial.print(mq135value, DEC);                 //data will be send bluetooth by myserial 
  
  // power led ON to indicate we start mesuring
  PowerLed.on();
  delay(100);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  // power led OFF end of mesure
  PowerLed.off();
}

