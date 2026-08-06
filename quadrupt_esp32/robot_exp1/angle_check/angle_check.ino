#include <Servo.h>

Servo myServo;

#define SERVO_PIN 2

void setup()
{
  Serial.begin(115200);

  myServo.attach(SERVO_PIN);

  myServo.write(90);

  Serial.println("Enter angle between 0 and 180:");
}

void loop()
{
  if (Serial.available())
  {
    int angle = Serial.parseInt();

    if (angle >= 0 && angle <= 360)
    {
      myServo.write(angle);

      Serial.print("Moved to: ");
      Serial.print(angle);
      Serial.println(" degrees");
    }
    else
    {
      Serial.println("Enter angle between 0 and 180");
    }

    while (Serial.available())
    {
      Serial.read();
    }
  }
}