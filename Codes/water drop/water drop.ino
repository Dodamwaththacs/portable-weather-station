void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int sensorReading = analogRead(A1);
  if (sensorReading < 700) {
    Serial.println("RAINING");
  }
  else {
    Serial.println("Normal");
  }
  // Serial.println(sensorReading);
  delay(2000);
}