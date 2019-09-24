// currently works only with version 2.4.2 of esp8266
#include <ESP8266WiFi.h>
#include "ESP8266SMTP.h"

const char* ssid = "Hemda";            		// WIFI network name
const char* password = "0507254614";        		// WIFI network password
uint8_t connection_state = 0;           // Connected to WIFI or not
uint16_t reconnect_interval = 10000;    // If not connected wait time to try again

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
	delay(2000);
	
	connection_state = WiFiConnect(ssid, password);
	uint32_t startTime = millis();
	
	SMTP.setEmail("lfirst960@gmail.com")
		.setPassword("1234a4321")
		.Subject("ESP8266SMTP Gmail test")
		.setFrom("ESP8266SMTP")
		.setForGmail();						// simply sets port to 465 and setServer("smtp.gmail.com");						
																   // message text from http://www.blindtextgenerator.com/lorem-ipsum
	if(SMTP.Send("shay.mrglit@gmail.com", "hello\n")) {
		Serial.println(F("Message sent"));
	} else {
		Serial.print(F("Error sending message: "));
		Serial.println(SMTP.getError());
	} 
	
	Serial.println(millis() - startTime);
}

void loop()
{}
