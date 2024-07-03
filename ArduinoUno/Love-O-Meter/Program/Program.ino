constexpr int sensorPin = A0;
float baselineTemp;

float getCurrentTemperature() {
  int sensorValue = analogRead(sensorPin);
  float voltage = (sensorValue/1024.0f) * 5.0f;
  float temperature = (voltage - 0.5f) * 100;
  
  // logging could be turned off
  Serial.print("Sensor value: ");
  Serial.print(sensorValue);
  
  Serial.print(", Volts: ");
  Serial.print(voltage);
  
  Serial.print(", degrees C: ");
  Serial.print(temperature);

  Serial.print("\n");

  return temperature;
}

float setBaselineTemp() {
  constexpr int iterationCount = 10;
  float temperatureSum = 0.0f;
  for (int i = 0; i < iterationCount; ++i) {
    temperatureSum += getCurrentTemperature();
    delay(1);
  }
  baselineTemp = temperatureSum / iterationCount;
}

void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  setBaselineTemp();
}

void loop() {
  delay(1);
  float currentTemperature = getCurrentTemperature();
  if (currentTemperature < baselineTemp + 1.5f) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (currentTemperature < baselineTemp + 3.0f) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (currentTemperature < baselineTemp + 4.5f) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
}
