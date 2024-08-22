constexpr int redLEDPin = 9;
constexpr int greenLEDPin = 10;
constexpr int blueLEDPin = 11;

constexpr int redControlPin = A0;
constexpr int greenControlPin = A1;
constexpr int blueControlPin = A2;

uint16_t redControlValue = 0;
uint16_t greenControlValue = 0;
uint16_t blueControlValue = 0;

// define for logging
// #define LOGS

#ifdef LOGS
constexpr int logBufferSize = 256;
char logBuffer[logBufferSize];
#endif

void setup() {
  #ifdef LOGS
  Serial.begin(9600);
  #endif
  // Serial.begin(9600);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  redControlValue = analogRead(redControlPin);
  delay(5);
  greenControlValue = analogRead(greenControlPin);
  delay(5);
  blueControlValue = analogRead(blueControlPin);
  delay(5);

  #ifdef LOGS
  sprintf(logBuffer, "Red value: %i \t Green value: %i \t Blue value: %i", (redControlValue >> 2), (greenControlValue >> 2), (blueControlValue >> 2));
  Serial.println(logBuffer);
  #endif

  analogWrite(redLEDPin, (redControlValue >> 2));
  analogWrite(greenLEDPin, (greenControlValue >> 2));
  analogWrite(blueLEDPin, (blueControlValue >> 2));
}
