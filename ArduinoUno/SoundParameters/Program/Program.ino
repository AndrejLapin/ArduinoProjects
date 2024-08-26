uint8_t pitchPin = A0;
uint8_t noteDelayPin = A1;

uint32_t pitch = 0;
uint32_t noteDelay = 10;
uint32_t lastTime = 0;
uint32_t currentTime = 0;
uint32_t delayElapsed = 0;

uint16_t pitchSensor;
uint16_t noteDelaySensor;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  currentTime = millis();
  noteDelaySensor = analogRead(noteDelayPin);
  noteDelay = map(noteDelaySensor, 0, 1023, 0, 500);
  delayElapsed += currentTime - lastTime;
  lastTime = currentTime;
  if (delayElapsed > noteDelay) {
    delayElapsed = 0;
    pitchSensor = analogRead(pitchPin);
    pitch = map(pitchSensor, 0, 1023, 50, 4000);
    tone(8, pitch, 10);
  }
}
