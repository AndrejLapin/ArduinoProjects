constexpr uint8_t switchPin = 8;
uint32_t previousTime = 0;

uint16_t switchState = 0;
uint16_t prevSwitchState = 0;

uint8_t led = 2;
int32_t interval = 1000;
constexpr uint16_t flashInterval = 100;

template<typename... Args>
void writePins(uint8_t value, Args&&... args) {
  (digitalWrite(args, value), ...);
}

void setup() {
  for (uint8_t x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }
  pinMode(switchPin, INPUT);
}

void loop() {
  uint32_t currentTime = millis();
  if (led < 8) {
    if (currentTime - previousTime > interval) {
      previousTime = currentTime;
      digitalWrite(led, HIGH);
      led++;
    }
  } else if (currentTime - previousTime > flashInterval) {
    previousTime = currentTime;
    writePins(led >= 9, 2, 3, 4, 5, 6, 7);
    led += (led < 9) - (led >= 9);
  }

  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState) {
    writePins(LOW, 2, 3, 4, 5, 6, 7);
    for(int x = 2; x < 8; x++) {
      digitalWrite(x, LOW);
    }

    led = 2;
    previousTime = currentTime;
  }
  prevSwitchState = switchState;
}
