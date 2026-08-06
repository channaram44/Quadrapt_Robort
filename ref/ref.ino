#include <Servo.h>

Servo servoBa1;
Servo servoBa2;
Servo servoBa3;
Servo servoBa4;

Servo servoHa1;
Servo servoHa2;
Servo servoHa3;
Servo servoHa4;

Servo servoKNa1;
Servo servoKNa2;
Servo servoKNa3;
Servo servoKNa4;

const int servoBa1pin = 2;   //front right
const int servoBa2pin = 5;   //front left
const int servoBa3pin = 8;   //back right
const int servoBa4pin = 11;  //back left

const int servoHa1Pin = 3;   // Front Right
const int servoHa2Pin = 6;   // front left
const int servoHa3Pin = 9;   // back right
const int servoHa4Pin = 12;  // back Left

const int servoKNa1Pin = 4;   // Front Right
const int servoKNa2Pin = 7;   // front left
const int servoKNa3Pin = 10;  // back right
const int servoKNa4Pin = 13;  // back Left

void walkForward() {

  for (int step = 0; step < 10; step++) {

    //---------------- STEP 1 ----------------//
    // Simultaneously micro-swing hips and micro-lift knee pair A (1 & 4)
    // Reduced angle movement limits used for tight, smooth strides
    for (int i = 0; i <= 30; i++) {
      int progressHA = map(i, 0, 30, 0, 12);  // Small hip swing angle (12 deg)
      int progressKN = map(i, 0, 30, 0, 25);  // Low knee lift angle (25 deg)

      servoHa1.write(90 + progressHA);
      servoHa4.write(90 - progressHA);
      servoHa2.write(90 + progressHA);
      servoHa3.write(90 - progressHA);

      servoKNa1.write(90 - progressKN);
      servoKNa4.write(90 - progressKN);

      delay(35); // Increased delay per increment for slower, seamless speed
    }

    // Lower Knee Pair A back to the ground smoothly
    for (int i = 30; i >= 0; i--) {
      int progressKN = map(i, 0, 30, 0, 25);
      servoKNa1.write(90 - progressKN);
      servoKNa4.write(90 - progressKN);
      delay(35);
    }

    //---------------- STEP 2 ----------------//
    // Simultaneously micro-swing hips opposite and micro-lift knee pair B (2 & 3)
    for (int i = 0; i <= 30; i++) {
      int progressHA = map(i, 0, 30, 0, 12);  // Small hip swing angle (12 deg)
      int progressKN = map(i, 0, 30, 0, 25);  // Low knee lift angle (25 deg)

      servoHa2.write(90 - progressHA);
      servoHa3.write(90 + progressHA);
      servoHa1.write(90 - progressHA);
      servoHa4.write(90 + progressHA);

      servoKNa2.write(90 - progressKN);
      servoKNa3.write(90 - progressKN);

      delay(35); // Slower movement speed
    }

    // Lower Knee Pair B back to the ground smoothly
    for (int i = 30; i >= 0; i--) {
      int progressKN = map(i, 0, 30, 0, 25);
      servoKNa2.write(90 - progressKN);
      servoKNa3.write(90 - progressKN);
      delay(35);
    }

    //---------------- Return Center ----------------//
    // Smoothly shift hips back to their center baseline position
    for (int i = 30; i >= 0; i--) {
      int progressHA = map(i, 0, 30, 0, 12);
      
      servoHa1.write(90 + progressHA);
      servoHa2.write(90 + progressHA);
      servoHa3.write(180 - (90 + progressHA));
      servoHa4.write(180 - (90 + progressHA));
      
      delay(35);
    }
  }
}

/***********************Setup**************************/
void setup() {
  Serial.begin(115200);

  servoHa3.attach(servoHa3Pin);
  servoHa1.attach(servoHa1Pin);
  servoHa4.attach(servoHa4Pin);
  servoHa2.attach(servoHa2Pin);

  servoKNa3.attach(servoKNa3Pin);
  servoKNa1.attach(servoKNa1Pin);
  servoKNa4.attach(servoKNa4Pin);
  servoKNa2.attach(servoKNa2Pin);

  servoBa1.attach(servoBa1pin);
  servoBa3.attach(servoBa3pin);
  servoBa2.attach(servoBa2pin);
  servoBa4.attach(servoBa4pin);

  // Set all connected servos to initial 90 degree home position
  servoBa1.write(90); servoBa2.write(90); servoBa3.write(90); servoBa4.write(90);
  servoHa1.write(90); servoHa2.write(90); servoHa3.write(90); servoHa4.write(90);
  servoKNa1.write(90); servoKNa2.write(90); servoKNa3.write(90); servoKNa4.write(90);

  Serial.println("Quadruped Robot Started");
  delay(1500); // Short buffer to let layout stabilize
}

void loop() {
  delay(500);

  //Sit();
  delay(500);

  //Stand();
  delay(500);

  //Set();
  delay(500);

  //Handshake();
  delay(500);

  //Set();
  delay(500);

  walkForward();
  delay(500);

  //Set();
  delay(500);

  //walkBackward();
  delay(500);

  //Set();
  delay(500);

  //Leftmove();
  delay(500);

  //Set();
  delay(500);

  //Rightmove();
  delay(500);

  //Set();
  delay(500);
}
