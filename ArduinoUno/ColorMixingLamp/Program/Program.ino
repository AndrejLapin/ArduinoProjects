constexpr int redLEDPin = 9;
constexpr int greenLEDPin = 10;
constexpr int blueLEDPin = 11;

constexpr int redSensorPin = A0;
constexpr int greenSensorPin = A1;
constexpr int blueSensorPin = A2;

// define in case RGB LED is not balanced correctly
// #define BALANCE_LEDS

#ifdef BALANCE_LEDS
constexpr float balanceRed = 0.5f;
constexpr float balanceGreen = 1.0f;
constexpr float balanceBlue = 0.5f;
#else
constexpr float balanceRed = 1.0f;
constexpr float balanceGreen = 1.0f;
constexpr float balanceBlue = 1.0f;
#endif

constexpr int stringBufferSize = 256;
char stringBuffer[stringBufferSize];

uint8_t redValue = 0;
uint8_t greenValue = 0;
uint8_t blueValue = 0;

uint16_t redSensorValue = 0;
uint16_t greenSensorValue = 0;
uint16_t blueSensorValue = 0;

void setup() {
  Serial.begin(9600);

  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);
  delay(5);

  // redSensorValue = 1023 >> 1;
  // greenSensorValue = 1023 >> 1;
  // blueSensorValue = 1023 >> 1;

  redValue = (redSensorValue >> 2) * balanceRed;
  greenValue = (greenSensorValue >> 2) * balanceGreen;
  blueValue = (blueSensorValue >> 2) * balanceBlue;

  sprintf(stringBuffer, "Raw Sensor Values \t red: %i\t green: %i\t blue: %i\t|\t Mapped Sensor Values \t red: %i\t green: %i\t blue: %i", 
    redSensorValue, greenSensorValue, blueSensorValue, redValue, greenValue, blueValue);
  Serial.println(stringBuffer);

  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}
