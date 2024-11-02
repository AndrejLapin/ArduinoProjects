import processing.serial.*;
Serial myPort;
PImage logo;
int bgcolor = 100;

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
  // for responsiveness only the last value should be important
  while (myPort.available() > 0) {
    bgcolor = myPort.read();
  }
  println(bgcolor);
  background(bgcolor, 255, 255);
  image(logo, 0, 0);
}
