#include <Servo.h>

// Hip Servos
Servo hipFL, hipFR, hipBL, hipBR;

// Knee Servos
Servo kneeFL, kneeFR, kneeBL, kneeBR;

// Pins
const int HIP_FL_PIN = 4;
const int HIP_FR_PIN = 5;
const int HIP_BL_PIN = 6;
const int HIP_BR_PIN = 7;

const int KNEE_FL_PIN = 8;
const int KNEE_FR_PIN = 9;
const int KNEE_BL_PIN = 10;
const int KNEE_BR_PIN = 11;

// Current Positions
int hipFLPos = 90;
int hipFRPos = 90;
int hipBLPos = 90;
int hipBRPos = 90;

int kneeFLPos = 90;
int kneeFRPos = 90;
int kneeBLPos = 90;
int kneeBRPos = 90;

// Smooth Servo Movement
void moveServo(Servo &servo, int &currentPos, int targetPos)
{
  if (currentPos < targetPos)
  {
    for (int p = currentPos; p <= targetPos; p++)
    {
      servo.write(p);
      delay(15);
    }
  }
  else
  {
    for (int p = currentPos; p >= targetPos; p--)
    {
      servo.write(p);
      delay(15);
    }
  }

  currentPos = targetPos;
}

// Stand Position
void standPose()
{
  Serial.println("Standing");

  moveServo(hipFL, hipFLPos, 90);
  moveServo(hipFR, hipFRPos, 90);
  moveServo(hipBL, hipBLPos, 90);
  moveServo(hipBR, hipBRPos, 90);

  moveServo(kneeFL, kneeFLPos, 90);
  moveServo(kneeFR, kneeFRPos, 90);
  moveServo(kneeBL, kneeBLPos, 90);
  moveServo(kneeBR, kneeBRPos, 90);
}

// Sit Position
void sitPose()
{
  Serial.println("Sitting");

  moveServo(hipFL, hipFLPos, 140);
  moveServo(hipFR, hipFRPos, 50);
  moveServo(hipBL, hipBLPos, 140);
  moveServo(hipBR, hipBRPos, 50);

  moveServo(kneeFL, kneeFLPos, 140);
  moveServo(kneeFR, kneeFRPos, 50);
  moveServo(kneeBL, kneeBLPos, 140);
  moveServo(kneeBR, kneeBRPos, 50);
}

void setup()
{
  Serial.begin(115200);

  hipFL.attach(HIP_FL_PIN);
  hipFR.attach(HIP_FR_PIN);
  hipBL.attach(HIP_BL_PIN);
  hipBR.attach(HIP_BR_PIN);

  kneeFL.attach(KNEE_FL_PIN);
  kneeFR.attach(KNEE_FR_PIN);
  kneeBL.attach(KNEE_BL_PIN);
  kneeBR.attach(KNEE_BR_PIN);

  // Start Standing
  standPose();

  delay(2000);
}

void loop()
{
  sitPose();
  delay(3000);

  standPose();
  delay(3000);
}