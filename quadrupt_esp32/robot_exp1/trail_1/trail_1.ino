#include <Servo.h>

// Servo objects
Servo servoFL;   // Front Left
Servo servoFR;   // Front Right
Servo servoBL;   // Back Left
Servo servoBR;   // Back Right

// GPIO pins
const int FL_PIN = 4;
const int FR_PIN = 5;
const int BL_PIN = 6;
const int BR_PIN = 7;

// --------------------
// Robot Positions
// --------------------

void standPosition()
{
  servoFL.write(90);
  servoFR.write(90);
  servoBL.write(90);
  servoBR.write(90);
}

void sitPosition()
{
  servoFL.write(45);
  servoFR.write(45);
  servoBL.write(45);
  servoBR.write(45);
}

// --------------------
// Movements
// --------------------

void moveForward()
{
  servoFL.write(120);
  servoBR.write(120);
  delay(300);

  servoFL.write(90);
  servoBR.write(90);
  delay(300);

  servoFR.write(120);
  servoBL.write(120);
  delay(300);

  servoFR.write(90);
  servoBL.write(90);
  delay(300);
}

void moveBackward()
{
  servoFL.write(60);
  servoBR.write(60);
  delay(300);

  servoFL.write(90);
  servoBR.write(90);
  delay(300);

  servoFR.write(60);
  servoBL.write(60);
  delay(300);

  servoFR.write(90);
  servoBL.write(90);
  delay(300);
}

void turnLeft()
{
  servoFL.write(60);
  servoBL.write(60);

  servoFR.write(120);
  servoBR.write(120);

  delay(500);

  standPosition();
}

void turnRight()
{
  servoFL.write(120);
  servoBL.write(120);

  servoFR.write(60);
  servoBR.write(60);

  delay(500);

  standPosition();
}

// --------------------
// Setup
// --------------------

void setup(
{
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servoFL.setPeriodHertz(50);
  servoFR.setPeriodHertz(50);
  servoBL.setPeriodHertz(50);
  servoBR.setPeriodHertz(50);

  servoFL.attach(FL_PIN, 500, 2400);
  servoFR.attach(FR_PIN, 500, 2400);
  servoBL.attach(BL_PIN, 500, 2400);
  servoBR.attach(BR_PIN, 500, 2400);

  standPosition();

  Serial.println("4-Servo Quadruped Test Started");
}

// --------------------
// Loop
// --------------------

void loop()
{
  Serial.println("Forward");
  moveForward();
  delay(1000);

  Serial.println("Backward");
  moveBackward();
  delay(1000);

  Serial.println("Left");
  turnLeft();
  delay(1000);

  Serial.println("Right");
  turnRight();
  delay(1000);

  Serial.println("Sit");
  sitPosition();
  delay(2000);

  Serial.println("Stand");
  standPosition();
  delay(2000);
}