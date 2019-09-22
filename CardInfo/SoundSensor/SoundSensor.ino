const int soundpin=A0;
const int threshold=200; // sets threshold value for sound sensor

void setup() {
  Serial.begin(9600);
  pinMode(soundpin,INPUT);
}

void loop() {
  int soundsens=analogRead(soundpin); // reads analog data from sound sensor
  Serial.println(soundsens);
  delay(1000);
}
