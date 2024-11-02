void setup() {
  Serial.begin(9600);
}

void loop() {
  // can be improved by taking multiple samples for the analog reads
  int val1 = analogRead(A0)/4;
  delay(2);
  int val2 = analogRead(A1)/4;
  delay(2);
  int val3 = analogRead(A2)/4;
  delay(2);

  // send message signature to signify start of message
  Serial.write(1);
  Serial.write(150);
  Serial.write(50);
  Serial.write(200);
  // now we write our values in order
  Serial.write(val1);
  Serial.write(val2);
  Serial.write(val3);
}
