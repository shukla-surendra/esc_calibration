#include <ESP32Servo.h>

// =====================================
// MOTOR PINS
// =====================================
#define FL 25
#define FR 26
#define RL 27
#define RR 14

// =====================================
// ESC RANGE
// =====================================
#define MIN_US 1000
#define MAX_US 2000

// =====================================
// SERVO OBJECTS
// =====================================
Servo motorFL;
Servo motorFR;
Servo motorRL;
Servo motorRR;

// =====================================
// WRITE ALL MOTORS
// =====================================
void writeAll(int us)
{
  motorFL.writeMicroseconds(us);
  motorFR.writeMicroseconds(us);
  motorRL.writeMicroseconds(us);
  motorRR.writeMicroseconds(us);
}

void setup()
{
  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("ESC CALIBRATION MODE");
  Serial.println("REMOVE ALL PROPELLERS");
  Serial.println("================================");

  // =================================
  // ALLOCATE PWM TIMERS
  // =================================
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // =================================
  // SET PWM FREQUENCY
  // =================================
  motorFL.setPeriodHertz(50);
  motorFR.setPeriodHertz(50);
  motorRL.setPeriodHertz(50);
  motorRR.setPeriodHertz(50);

  // =================================
  // ATTACH ESC PINS
  // =================================
  motorFL.attach(FL, MIN_US, MAX_US);
  motorFR.attach(FR, MIN_US, MAX_US);
  motorRL.attach(RL, MIN_US, MAX_US);
  motorRR.attach(RR, MIN_US, MAX_US);

  // =================================
  // STEP 1
  // =================================
  Serial.println();
  Serial.println("Disconnect ESC battery NOW");
  delay(5000);

  // =================================
  // STEP 2 - SEND MAX THROTTLE
  // =================================
  Serial.println();
  Serial.println("Sending MAX throttle...");
  writeAll(MAX_US);

  Serial.println("Connect ESC battery NOW");
  Serial.println("Wait for calibration beeps");

  delay(8000);

  // =================================
  // STEP 3 - SEND MIN THROTTLE
  // =================================
  Serial.println();
  Serial.println("Sending MIN throttle...");
  writeAll(MIN_US);

  Serial.println("Waiting for confirmation beeps");

  delay(8000);

  // =================================
  // DONE
  // =================================
  Serial.println();
  Serial.println("================================");
  Serial.println("ESC CALIBRATION COMPLETE");
  Serial.println("================================");

  // Safety
  writeAll(MIN_US);
}

void loop()
{
}