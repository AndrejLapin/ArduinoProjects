#include <Servo.h>
Servo myServo;

constexpr int piezo = A0;
constexpr int switchPin = 2;
constexpr int yellowLed = 3;
constexpr int greenLed = 4;
constexpr int redLed = 5;

int knockVal;
int switchVal;

constexpr int quietKnock = 10;
constexpr int loudKnock = 100;

bool locked = false;
int numberOfKnocks = 0;

void setup() {
  myServo.attach(9);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  digitalWrite(greenLed, HIGH);
  myServo.write(0);
  Serial.print("The box is unloced!");
}

void loop() {
  if (!locked) {
    switchVal = digitalRead(switchPin);
    if (switchVal == HIGH) {
      locked = true;
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      myServo.write(90);
      Serial.println("The box is loced!");
      delay(1000);
    }
  }
  else {
    knockVal = analogRead(piezo);
    if (numberOfKnocks < 3 && knockVal > 0) {
      if (checkForKnock(knockVal)) {
        numberOfKnocks++;
      }
      Serial.print(3 - numberOfKnocks);
      Serial.println(" more knocks to go");
    }

    if (numberOfKnocks >= 3) {
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      Serial.println("The box is unlocked!");
      numberOfKnocks = 0;
    }
  }
}

bool checkForKnock(int value) {
  if (value > quietKnock && value < loudKnock) {
    digitalWrite(yellowLed, HIGH);
    // avoid such blocking delays, get into the blinking state
    delay(50);
    digitalWrite(yellowLed, LOW);
    Serial.print("Valid knock of value ");
    Serial.println(value);
    return true;
  }
  Serial.print("Bad knock value ");
  Serial.println(value);
  return false;
}
