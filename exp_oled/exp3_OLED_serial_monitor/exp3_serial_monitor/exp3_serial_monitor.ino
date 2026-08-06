#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//=================================================
// OLED
//=================================================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1);

//=================================================
// SERVOS
//=================================================
Servo servoB1;
Servo servoB2;
Servo servoB3;
Servo servoB4;

Servo servoH1;
Servo servoH2;
Servo servoH3;
Servo servoH4;

Servo servoKN1;
Servo servoKN2;
Servo servoKN3;
Servo servoKN4;

//=================================================
// PINS
//=================================================
const int servoB1pin = 2;  // front right
const int servoB2pin = 3;  // back right
const int servoB3pin = 4;  // front left
const int servoB4pin = 5;  // back left

const int servoH1Pin = 6;  // back right
const int servoH2Pin = 7;  // front right
const int servoH3Pin = 8;  // back left
const int servoH4Pin = 9;  // front left

const int servoKN1Pin = 10;  // back right
const int servoKN2Pin = 11;  // front right
const int servoKN3Pin = 12;  // back left
const int servoKN4Pin = 13;  // front left

//=================================================
// ROBOT STATE
//=================================================
String currentAction = "CENTER";

//=================================================
// OLED UPDATE
//=================================================
void updateOLED(String action) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Quadruped Robot");

  display.println("----------------");

  display.print("Action:");
  display.println(action);

  display.display();
}

//=================================================
// CENTER POSITION
//=================================================
void CenterPose() {
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

  delay(500);
}
//=================================================
// SIT
//=================================================
void Sit() {
  for (int i = 90; i >= 0; i--) {
    servoH2.write(i);
    servoH3.write(i);

    servoKN2.write(constrain(i - 45, 0, 180));
    servoKN3.write(constrain(i - 45, 0, 180));

    servoH1.write(180 - i);
    servoH4.write(180 - i);
    
    servoKN1.write(constrain(230 - i, 0, 180));
    servoKN4.write(constrain(230 - i, 0, 180));

    delay(80);
  }
}

//=================================================
// STAND
//=================================================
void Stand() {
  for (int i = 0; i <= 90; i++) {
    servoH2.write(i);
    servoH3.write(i);

    servoKN2.write(constrain(i - 45, 0, 180));
    servoKN3.write(constrain(i - 45, 0, 180));

    servoH1.write(180 - i);
    servoH4.write(180 - i);
    
    servoKN1.write(constrain(230 - i, 0, 180));
    servoKN4.write(constrain(230 - i, 0, 180));

    delay(50);
  }
}
/**************** walk Forward ******************/
void walkForward() {
  // Repeat walking cycle
  for (int step = 0; step < 10; step++) {
    //---------------- STEP 1 ----------------//
    for (int i = 90; i >= 70; i--) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }

    // Lift Legs 1 & 4
    for (int k = 90; k >= 70; k--) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    // Lower Legs 1 & 4
    for (int k = 70; k <= 90; k++) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    //---------------- STEP 2 ----------------//
    for (int i = 70; i <= 110; i++) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }

    // Lift Legs 2 & 3
    for (int k = 90; k >= 70; k--) {
      servoKN2.write(k);
      servoKN4.write(k);
      delay(50);
    }
    //---------------- Return Center ----------------//
    for (int i = 110; i >= 90; i--) {
      servoH1.write(i);
      servoH3.write(i);

      servoH2.write(180 - i);
      servoH4.write(180 - i);

      delay(50);
    }
  }

  delay(30);
}
 void walkBackward() {

  for (int step = 0; step < 10; step++) {

    for (int i = 90; i <= 110; i++) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);
      delay(50);
    }

    for (int k = 90; k <= 110; k++) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    for (int k = 110; k >= 90; k--) {
      servoKN1.write(k);
      servoKN3.write(k);
      delay(50);
    }

    for (int i = 110; i >= 70; i--) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);
      delay(50);
    }

    for (int k = 90; k <= 110; k++) {
      servoKN2.write(k);
      servoKN4.write(k);
      delay(50);
    }

    for (int k = 110; k >= 90; k--) {
      servoKN2.write(k);
      servoKN4.write(k);
      delay(50);
    }

    for (int i = 70; i <= 90; i++) {
      servoH1.write(i);
      servoH3.write(i);
      servoH2.write(180 - i);
      servoH4.write(180 - i);
      delay(50);
    }
  }

  delay(30);
}
 void Rightmove() {

  for (int step = 0; step < 5; step++) {

    for (int i = 70; i <= 110; i++) {
      servoB1.write(90);
      servoB3.write(i);
      servoKN2.write(i);
      servoB2.write(180 - i);
      servoB4.write(90);
      delay(50);
    }

    for (int i = 110; i >= 70; i--) {
      servoB1.write(90);
      servoB3.write(i);
      servoKN2.write(i);
      servoB2.write(180 - i);
      servoB4.write(90);
      delay(50);
    }
  }
}
void Leftmove() {

  for (int step = 0; step < 5; step++) {

    for (int i = 110; i >= 70; i--) {
      servoB3.write(90);
      servoB1.write(i);
      servoKN4.write(i);
      servoB4.write(180 - i);
      servoB2.write(90);
      delay(80);
    }

    for (int i = 70; i <= 110; i++) {
      servoB3.write(90);
      servoB1.write(i);
      servoKN1.write(i);
      servoB4.write(180 - i);
      servoB2.write(90);
      delay(80);
    }
  }
}
  void Handshake() {

  servoB2.write(120);
  servoB3.write(60);
  servoB4.write(90);

  servoH1.write(80);
  servoH2.write(150);
  servoH3.write(130);
  servoH4.write(80);

  servoKN1.write(90);
  servoKN3.write(90);
  servoKN4.write(90);

  for (int i = 0; i < 10; i++) {

    servoB1.write(70);
    delay(300);

    servoB1.write(90);
    delay(300);

    servoKN2.write(40);
    delay(200);

    servoKN2.write(70);
    delay(200);
  }

  CenterPose();
  updateOLED("CENTER");
}
    //=================================================
    // SETUP
    //=================================================
    void setup() {
      Serial.begin(115200);

      servoH1.attach(servoH1Pin);
      servoH2.attach(servoH2Pin);
      servoH3.attach(servoH3Pin);
      servoH4.attach(servoH4Pin);

      servoKN1.attach(servoKN1Pin);
      servoKN2.attach(servoKN2Pin);
      servoKN3.attach(servoKN3Pin);
      servoKN4.attach(servoKN4Pin);

      servoB1.attach(servoB1pin);
      servoB2.attach(servoB2pin);
      servoB3.attach(servoB3pin);
      servoB4.attach(servoB4pin);

      if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (1)
          ;
      }

      display.clearDisplay();
      display.display();

      updateOLED("READY");

      CenterPose();

      Serial.println("Quadruped Robot Ready");

      Serial.println("F = Forward");
      Serial.println("B = Backward");
      Serial.println("L = Left");
      Serial.println("R = Right");
      Serial.println("S = Sit");
      Serial.println("T = Stand");
      Serial.println("H = Handshake");
      Serial.println("C = Center");
    }

    //=================================================
    // LOOP
    //=================================================
    void loop() {
      if (Serial.available()) {
        char cmd = toupper(Serial.read());

        switch (cmd) {
          case 'F':
            currentAction = "FORWARD";
            updateOLED(currentAction);
            walkForward();
            break;

          case 'B':
            currentAction = "BACKWARD";
            updateOLED(currentAction);
            walkBackward();
            break;

          case 'L':
            currentAction = "LEFT";
            updateOLED(currentAction);
            Leftmove();
            break;

          case 'R':
            currentAction = "RIGHT";
            updateOLED(currentAction);
            Rightmove();
            break;

          case 'S':
            currentAction = "SIT";
            updateOLED(currentAction);
            Sit();
            break;

          case 'T':
            currentAction = "STAND";
            updateOLED(currentAction);
            Stand();
            break;

          case 'H':
            currentAction = "HANDSHAKE";
            updateOLED(currentAction);
            Handshake();
            break;

          case 'C':
            currentAction = "CENTER";
            updateOLED(currentAction);
            CenterPose();
            break;
        }
      }
    }