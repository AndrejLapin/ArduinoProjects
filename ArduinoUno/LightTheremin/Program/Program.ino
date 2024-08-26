int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

const int ledPin = 13;

// #define LOGS

#ifdef LOGS
constexpr int logBufferSize = 256;
char logBuffer[logBufferSize];
#endif

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
#ifdef LOGS
  Serial.begin(9600);
#endif

  while(millis() < 5000) {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
#ifdef LOGS
  sprintf(logBuffer, "Sensor high is: %i \t sensor low is: %i", sensorHigh, sensorLow);
  Serial.println(logBuffer);
  delay(1000);
#endif
  digitalWrite(ledPin, LOW);
}

void loop() {
  sensorValue = analogRead(A0);
  int pitch = map(sensorValue, sensorLow, sensorHigh, 2500, 50);
#ifdef LOGS
  sprintf(logBuffer, "Sensor value is: %i \t pitch value is: %i", sensorValue, pitch);
  Serial.println(logBuffer);
#endif

  tone(8, pitch, 20);
  delay(10);
}
