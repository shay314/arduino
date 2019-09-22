#include <SPI.h>
#include <SD.h>
#include "DHT.h"

#define SLEEP_TIME_IN_MILI_SEC 1000 * 10
#define FILE_PATH "datalog.txt"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


const int chipSelect = 15;
const int soundpin=A0;

void setup() {
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  if (SD.exists(FILE_PATH)) {
    Serial.println("Removing file: " + String(FILE_PATH));
    SD.remove(FILE_PATH); 
  }

  // init temperture sensor
  dht.begin();

  // init sound sensor
  pinMode(soundpin,INPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(SLEEP_TIME_IN_MILI_SEC);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // read sound
  int soundsens = analogRead(soundpin);
  
  File dataFile = SD.open(FILE_PATH, FILE_WRITE);
  String dataString = "Humidity: " + String(h) + " Temperature: " + String(t) + " Sounds: "+ String(soundsens) + "\n";

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.print(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
