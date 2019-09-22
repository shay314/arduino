// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
  
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN            4         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11     // DHT 11 

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  
  // Initialize device.
  dht.begin();
}

void loop() {
  // Get temperature event and print its value.
  sensors_event_t event;  

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  delay(1000);
}
