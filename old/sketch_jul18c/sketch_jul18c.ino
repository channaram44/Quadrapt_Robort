#include "Quadruped.h"

Quadruped robot(48.302, 91, 15.151, 40, 40);

// ---------------- STAND ----------------
void standPose() {
  robot.initialise();
  delay(5000);
}

// ---------------- SIT ----------------
void sitPose() {
  robot.IK_one_leg("rf", 0, 20, 20);
  robot.IK_one_leg("lf", 0, 20, 20);
  robot.IK_one_leg("rb", 0, 20, 20);
  robot.IK_one_leg("lb", 0, 20, 20);
  delay(5000);
}

// ---------------- FORWARD STEP ----------------
void stepForward(String leg) {

  robot.translate_cog_on_support_polygon(leg);

  // Lift and move forward
  robot.IK_one_leg(leg, 15, 0, 20);
  delay(5000);

  // Put down
  robot.IK_one_leg(leg, 0, 0, -20);
  delay(5000);

  // Return body position
  robot.IK_one_leg(leg, -15, 0, 0);
  delay(5000);
}

// ---------------- BACKWARD STEP ----------------
void stepBackward(String leg) {

  robot.translate_cog_on_support_polygon(leg);

  // Lift and move backward
  robot.IK_one_leg(leg, -15, 0, 20);
  delay(5000);

  // Put down
  robot.IK_one_leg(leg, 0, 0, -20);
  delay(5000);

  // Return body position
  robot.IK_one_leg(leg, 15, 0, 0);
  delay(5000);
}

// ---------------- WALK FORWARD ----------------
void walkForward() {

  stepForward("rf");
  stepForward("lb");

  stepForward("lf");
  stepForward("rb");
}

// ---------------- WALK BACKWARD ----------------
void walkBackward() {

  stepBackward("rf");
  stepBackward("lb");

  stepBackward("lf");
  stepBackward("rb");
}

void setup() {

  Serial.begin(9600);

  standPose();

  delay(2000);

  sitPose();

  delay(2000);

  standPose();
}

void loop() {

  walkForward();

  delay(5000);

  walkBackward();

  delay(5000);
}