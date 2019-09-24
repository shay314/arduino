int MOISTURE_PIN = A0; 

void setup() {
  Serial.begin(115200);
  pinMode(MOISTURE_PIN, INPUT); //Set pin 8 as input pin, to receive data from Soil moisture sensor.
}

void loop() { 
  float val = analogRead(MOISTURE_PIN); 
  Serial.print(val, 3);
  Serial.print('\n');
  delay(3000);
}
