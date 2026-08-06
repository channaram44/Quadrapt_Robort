#include <ESP32Servo.h>

Servo servo1, servo2, servo3, servo4;
Servo servo5, servo6, servo7, servo8;

const int pins[8] = {4, 5, 12, 13};

void setup() {
  servo1.attach(pins[0]);
  servo2.attach(pins[1]);
  servo3.attach(pins[2]);
  servo4.attach(pins[3]);

}

void forwardMove() {
  servo1.write(120);
  servo2.write(120);
  servo3.write(120);
  servo4.write(120);

}

void reverseMove() {
  servo1.write(60);
  servo2.write(60);
  servo3.write(60);
  servo4.write(60);

}

void loop() {
  forwardMove();
  delay(1000);

  reverseMove();
  delay(1000);
}