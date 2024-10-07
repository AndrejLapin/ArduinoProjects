constexpr int controlPin1 = 2;
constexpr int controlPin2 = 3;
constexpr int enablePin = 9;
constexpr int directionSwitchPin = 4;
constexpr int onOffSwitchStateSwitchPin = 5;
constexpr int potPin = A0;
bool previousOnOffSwitchState = false;
bool previousDirectionSwitchState = false;

enum class Direction : bool {
  Forward,
  Backward
};
Direction motorDirection = Direction::Forward;
bool motorEnabled = false;
int motorSpeed = 0;

template<typename... Args>
void printOut(Args&&... args) {
  (Serial.print(args), ...);
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, OUTPUT);
}

void loop() {
  int pinState = digitalRead(onOffSwitchStateSwitchPin);
  // printOut("Switch PIN state: ", pinState);
  if (previousOnOffSwitchState != pinState && pinState) {
      motorEnabled = !motorEnabled;
      printOut("Motor enabled with val: ", motorEnabled);
  }
  previousOnOffSwitchState = pinState;

  pinState = digitalRead(directionSwitchPin);
  if (previousDirectionSwitchState != pinState && pinState) {
    motorDirection = static_cast<Direction>(!static_cast<bool>(motorDirection));
  }
  previousDirectionSwitchState = pinState;

  if (motorDirection == Direction::Backward) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  motorSpeed = analogRead(potPin) / 4;

  if (motorEnabled == HIGH) {
    printOut("Motor eshould run with speed ", motorSpeed, " and direction ", static_cast<bool>(motorDirection));
    analogWrite(enablePin, motorSpeed);
  } else {
    analogWrite(enablePin, 0);
  }
}
