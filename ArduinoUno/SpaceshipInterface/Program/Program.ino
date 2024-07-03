constexpr int blinkDelayMillis = 250;
unsigned long previousTime = 0;
unsigned long cycleTime = 0;
bool switchState = LOW;
bool lastInput = LOW;
bool pin4State = LOW;
bool pin5State = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  unsigned long deltaTime;
  {
    unsigned long currentTime = millis();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
  }

  {
    int input = digitalRead(2);
    if (input == HIGH && lastInput == LOW) {
      switchState = !switchState;
      cycleTime = 0;
    }
    lastInput = input;
  }

  if (switchState == LOW) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else {
    digitalWrite(3, LOW);
    digitalWrite(4, pin4State);
    digitalWrite(5, pin5State);
    cycleTime += deltaTime;
    if (cycleTime >= blinkDelayMillis) {
      pin4State = !pin4State;
      pin5State = !pin5State;
      cycleTime -= blinkDelayMillis;
    }
  }
}
