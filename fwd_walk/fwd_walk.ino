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

// Movement configuration variables for smoothness adjustments
const int stepDelay = 25;     // Speed control (lower value = faster movement)
const int liftAngle = 45;     // Knee vertical clearance height 
const int swingAngle = 20;    // Hip stride depth

/**************** SET ALL SERVOS TO 90° ****************/
void Set() {
  // Body servos
  servoBa1.write(90);
  servoBa3.write(90);
  servoBa2.write(90);
  servoBa4.write(90);

  // Hip servos
  servoHa3.write(90);
  servoHa1.write(90);
  servoHa4.write(90);
  servoHa2.write(90);

  // Knee servos
  servoKNa3.write(90);
  servoKNa1.write(90);
  servoKNa4.write(90);
  servoKNa2.write(90);

  delay(500);
}

/****************sit*****************/
void Sit() {
  for (int i = 90; i >= 0; i--) {
    // Left pair
    servoHa1.write(i);
    servoHa4.write(i);
    servoKNa1.write(i - 45);
    servoKNa4.write(i - 45);

    // Right pair
    servoHa3.write(180 - i);
    servoHa2.write(180 - i);
    servoKNa3.write(230 - i);
    servoKNa2.write(230 - i);

    delay(80);  // Same speed as Stand
  }
  delay(60);
}

/******************stand robot********************/
void Stand() {
  for (int i = 0; i <= 90; i++) {
    // Left pair
    servoHa1.write(i);
    servoHa4.write(i);
    servoKNa1.write(i - 45);
    servoKNa4.write(i - 45);

    // Right pair
    servoHa3.write(180 - i);
    servoHa2.write(180 - i);
    servoKNa3.write(230 - i);
    servoKNa2.write(230 - i);

    delay(50);  
  }
  delay(50);
  Set();
}

/**************** SMOOTH WALK FORWARD ******************/
void walkForward() {
  for (int step = 0; step < 10; step++) {
    
    //---------------- STEP 1: Lift Pair A & Swing Hips ----------------//
    for (int i = 0; i <= swingAngle; i++) {
      int progress = map(i, 0, swingAngle, 0, liftAngle);
      
      // Smooth vertical lift (Front Right + Back Left)
      servoKNa1.write(90 - progress); 
      servoKNa4.write(90 - progress);
      
      // Smooth synchronized hip movement
      servoHa1.write(90 + i); 
      servoHa4.write(90 - i); 
      servoHa2.write(90 + i); 
      servoHa3.write(90 - i); 
      
      delay(stepDelay);
    }

    //---------------- STEP 2: Ground Pair A ----------------//
    for (int i = liftAngle; i >= 0; i--) {
      servoKNa1.write(90 - i);
      servoKNa4.write(90 - i);
      delay(stepDelay);
    }

    //---------------- STEP 3: Lift Pair B & Swing Hips Opposite ----------------//
    for (int i = 0; i <= swingAngle; i++) {
      int progress = map(i, 0, swingAngle, 0, liftAngle);
      
      // Smooth vertical lift (Front Left + Back Right)
      servoKNa2.write(90 - progress); 
      servoKNa3.write(90 - progress);
      
      // Smooth synchronized hip movement
      servoHa2.write(90 - i); 
      servoHa3.write(90 + i); 
      servoHa1.write(90 - i); 
      servoHa4.write(90 + i); 
      
      delay(stepDelay);
    }

    //---------------- STEP 4: Ground Pair B ----------------//
    for (int i = liftAngle; i >= 0; i--) {
      servoKNa2.write(90 - i);
      servoKNa3.write(90 - i);
      delay(stepDelay);
    }
  }
  delay(30);
}

/**************** SMOOTH WALK BACKWARD ****************/
void walkBackward() {
  for (int step = 0; step < 10; step++) {
    
    //---------------- STEP 1: Lift Pair A & Swing Hips Backwards ----------------//
    for (int i = 0; i <= swingAngle; i++) {
      int progress = map(i, 0, swingAngle, 0, liftAngle);
      
      servoKNa1.write(90 - progress); 
      servoKNa4.write(90 - progress);
      
      // Mirrored directions for backwards motion
      servoHa1.write(90 - i); 
      servoHa4.write(90 + i); 
      servoHa2.write(90 - i); 
      servoHa3.write(90 + i); 
      
      delay(stepDelay);
    }

    //---------------- STEP 2: Ground Pair A ----------------//
    for (int i = liftAngle; i >= 0; i--) {
      servoKNa1.write(90 - i);
      servoKNa4.write(90 - i);
      delay(stepDelay);
    }

    //---------------- STEP 3: Lift Pair B & Swing Hips Opposite Backwards ----------------//
    for (int i = 0; i <= swingAngle; i++) {
      int progress = map(i, 0, swingAngle, 0, liftAngle);
      
      servoKNa2.write(90 - progress); 
      servoKNa3.write(90 - progress);
      
      // Mirrored directions for backwards motion
      servoHa2.write(90 + i); 
      servoHa3.write(90 - i); 
      servoHa1.write(90 + i); 
      servoHa4.write(90 - i); 
      
      delay(stepDelay);
    }

    //---------------- STEP 4: Ground Pair B ----------------//
    for (int i = liftAngle; i >= 0; i--) {
      servoKNa2.write(90 - i);
      servoKNa3.write(90 - i);
      delay(stepDelay);
    }
  }
  delay(30);
}

/*****************right move**********************/
void Rightmove() {
  for (int step = 0; step < 5; step++) {
    for (int i = 70; i <= 110; i++) {
      servoBa1.write(90);
      servoBa2.write(i);
      servoKNa1.write(i);
      servoBa3.write(180 - i);
      servoBa4.write(90);
      delay(50);
    }
    for (int i = 110; i >= 70; i--) {
      servoBa1.write(90);
      servoBa2.write(i);
      servoKNa1.write(i);
      servoBa3.write(180 - i);
      servoBa4.write(90);
      delay(50);
    }
    delay(40);
  }
}

/************************left move***************/
void Leftmove() {
  for (int step = 0; step < 5; step++) {
    for (int i = 110; i >= 70; i--) {
      servoBa2.write(90);
      servoBa1.write(i);
      servoKNa2.write(i);
      servoBa4.write(180 - i);
      servoBa3.write(90);
      delay(80);
    }
    delay(40);

    for (int i = 70; i <= 110; i++) {
      servoBa2.write(90);
      servoBa1.write(i);
      servoKNa3.write(i);
      servoBa4.write(180 - i);
      servoBa3.write(90);
      delay(80);
    }
    delay(40);
  }
}

/*******************hand shake*****************/
void Handshake() {
  servoBa3.write(90);   servoBa2.write(90);   servoBa4.write(90);
  servoHa3.write(90);   servoHa4.write(90);   servoHa2.write(90);
  servoKNa3.write(90);  servoKNa4.write(90);  servoKNa2.write(90);

  for (int i = 0; i < 2; i++) {
    servoHa1.write(150);
    servoBa1.write(85);
    delay(800);

    servoBa1.write(95);
    delay(800);

    servoKNa1.write(40);
    delay(200);

    servoKNa1.write(70);
    delay(200);
    servoHa1.write(90);
  }
  delay(500);
  Set();
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

  Set(); // Resets layout before loop execution
  Serial.println("Quadruped Robot Started");
}

/***********************Loop **************************/
void loop() {
  walkForward();
  delay(500);

  Set()
  delay(500);
}
