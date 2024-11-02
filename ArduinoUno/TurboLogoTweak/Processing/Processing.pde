import processing.serial.*;
Serial myPort;
PImage logo;
int hue = 255;
int saturation = 255;
int brightness = 255;
final int[] messageStartSignature = {1, 150, 50, 200};
final int dataLength = 3;
final int maxBuffer = 2 * messageStartSignature.length + dataLength;

void setup() {
  size(1, 1);
  surface.setResizable(true);
  colorMode(HSB, 255);
  
  logo = loadImage("https://siminnovations.com/wiki/images/7/7a/Arduino_logo_round.png");
  surface.setSize(logo.width, logo.height);
  println("Available serial ports: ");
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[1], 9600);
}

void draw() {
  if(myPort.available() > maxBuffer) {
    myPort.readBytes(myPort.available() - maxBuffer);
  }
  
  int matchCount = 0;
  boolean signatureMatched = false;
  while(!signatureMatched) {
    while(myPort.available() < 1) {
      delay(1); //<>//
    }
    int val = myPort.read();
    if (val == messageStartSignature[matchCount]) {
      matchCount += 1;
      if (matchCount == messageStartSignature.length) {
        signatureMatched = true;
      }
    } else {
      matchCount = 0;
    }
  }
  
  int parsedAmount = 0;
  while(parsedAmount < 3) {
    while(myPort.available() < 1) {
      delay(1); //<>//
    }
    if (parsedAmount < 1) {
      hue = myPort.read();
      parsedAmount += 1;
    } else if (parsedAmount < 2) {
      saturation = myPort.read();
      parsedAmount += 1;
    } else if (parsedAmount < 3) {
      brightness = myPort.read();
      parsedAmount += 1;
    }
  }
  background(hue, saturation, brightness);
  image(logo, 0, 0);
}
