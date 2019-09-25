// currently works only with version 2.4.2 of esp8266
#include <ESP8266WiFi.h>
#include "ESP8266SMTP.h"

const char* ssid = "Hemda";            		// WIFI network name
const char* password = "0507254614";        		// WIFI network password

uint16_t reconnect_interval = 10000;    // If not connected wait time to try again
int TIME_BETWEEN_NOTIFICATION_MICRO_SECONDS = 1e6 * 60 * 60 * 12;

int MOISTURE_PIN = A0; 

uint8_t WiFiConnect(const char* ssID, const char* nPassword)
{
	static uint16_t attempt = 0;
	Serial.print("Connecting to ");
	Serial.println(ssID);
	WiFi.begin(ssID, nPassword);

	uint8_t i = 0;
	while(WiFi.status() != WL_CONNECTED && i++ < 50) {
		delay(200);
		Serial.print(".");
	}
	++attempt;
	Serial.println("");
	if(i == 51) {
		Serial.print(F("Connection: TIMEOUT on attempt: "));
		Serial.println(attempt);
		if(attempt % 2 == 0)
			Serial.println(F("Check if access point available or SSID and Password are correct\r\n"));
		return false;
	}
	Serial.println(F("Connection: ESTABLISHED"));
	Serial.print(F("Got IP address: "));
	Serial.println(WiFi.localIP());
	return true;
}

void setup()
{
	Serial.begin(115200);

  // connect to wifi
	WiFiConnect(ssid, password);

  //Set pin 8 as input pin, to receive data from Soil moisture sensor.
  pinMode(MOISTURE_PIN, INPUT);

  // sample the sensor
  float value = analogRead(MOISTURE_PIN); 

  // send the mail
  SMTP.setEmail("lfirst960@gmail.com")
    .setPassword("1234a4321")
    .Subject("Moisture status")
    .setFrom("Garden")
    .setForGmail();

  String message = "";
  message = message + "Sensor value: " + value + "\n";
  if(SMTP.Send("shayma@mobileye.com", message)) {
    Serial.println(F("Message sent"));
  } else {
    Serial.print(F("Error sending message: "));
    Serial.println(SMTP.getError());
  }
  
  ESP.deepSleep(TIME_BETWEEN_NOTIFICATION_MICRO_SECONDS);
}

void loop()
{}
