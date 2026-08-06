#include <Servo.h>

// Body Servos
Servo servoB1, servoB2, servoB3, servoB4;

// Hip Servos
Servo servoH1, servoH2, servoH3, servoH4;

// Knee Servos
Servo servoKN1, servoKN2, servoKN3, servoKN4;

// Pin Definitions
const int servoB1pin = 2;
const int servoB2pin = 3;
const int servoB3pin = 4;
const int servoB4pin = 5;

const int servoH1Pin = 6;
const int servoH2Pin = 7;
const int servoH3Pin = 8;
const int servoH4Pin = 9;

const int servoKN1Pin = 10;
const int servoKN2Pin = 11;
const int servoKN3Pin = 12;
const int servoKN4Pin = 13;

void setup()
{
  // Attach Body Servos
  servoB1.attach(servoB1pin);
  servoB2.attach(servoB2pin);
  servoB3.attach(servoB3pin);
  servoB4.attach(servoB4pin);

  // Attach Hip Servos
  servoH1.attach(servoH1Pin);
  servoH2.attach(servoH2Pin);
  servoH3.attach(servoH3Pin);
  servoH4.attach(servoH4Pin);

  // Attach Knee Servos
  servoKN1.attach(servoKN1Pin);
  servoKN2.attach(servoKN2Pin);
  servoKN3.attach(servoKN3Pin);
  servoKN4.attach(servoKN4Pin);

  delay(1000);

  // Set all servos to 90 degrees
  servoB1.write(90);
  servoB2.write(90);
  servoB3.write(90);
  servoB4.write(90);

  servoH1.write(90);
  servoH2.write(90);
  servoH3.write(90);
  servoH4.write(90);

  servoKN1.write(90);
  servoKN2.write(90);
  servoKN3.write(90);
  servoKN4.write(90);
}

void loop()
{
  // Nothing here
}