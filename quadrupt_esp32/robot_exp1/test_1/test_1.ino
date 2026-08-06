#include <ESP32Servo.h>

Servo FL;
Servo FR;
Servo RL;
Servo RR;

#define FL_PIN 4
#define FR_PIN 5
#define RL_PIN 6
#define RR_PIN 7

void moveSmooth(Servo &servo, int from, int to)
{
  if(from < to)
  {
    for(int a = from; a <= to; a++)
    {
      servo.write(a);
      delay(10);
    }
  }
  else
  {
    for(int a = from; a >= to; a--)
    {
      servo.write(a);
      delay(10);
    }
  }
}

void standPose()
{
  FL.write(90);
  FR.write(90);
  RL.write(90);
  RR.write(90);
}

void walkForward()
{
  // Diagonal pair 1
  moveSmooth(FL, 90, 60);
  moveSmooth(RR, 90, 60);

  moveSmooth(FL, 60, 90);
  moveSmooth(RR, 60, 90);

  // Diagonal pair 2
  moveSmooth(FR, 90, 60);
  moveSmooth(RL, 90, 60);

  moveSmooth(FR, 60, 90);
  moveSmooth(RL, 60, 90);
}

void walkBackward()
{
  // Diagonal pair 1
  moveSmooth(FL, 90, 120);
  moveSmooth(RR, 90, 120);

  moveSmooth(FL, 120, 90);
  moveSmooth(RR, 120, 90);

  // Diagonal pair 2
  moveSmooth(FR, 90, 120);
  moveSmooth(RL, 90, 120);

  moveSmooth(FR, 120, 90);
  moveSmooth(RL, 120, 90);
}

void setup()
{
  Serial.begin(115200);

  FL.attach(FL_PIN, 500, 2400);
  FR.attach(FR_PIN, 500, 2400);
  RL.attach(RL_PIN, 500, 2400);
  RR.attach(RR_PIN, 500, 2400);

  delay(1000);

  standPose();
}

void loop()
{
  walkForward();
}