#include "MotorController.h"

MotorController::MotorController() : current_speed_(config::speed::kStopped) {}

void MotorController::Initialize() {
  // Direction pins
  pinMode(config::pins::kMotorM1, OUTPUT);
  pinMode(config::pins::kMotorM2, OUTPUT);
  pinMode(config::pins::kMotorN1, OUTPUT);
  pinMode(config::pins::kMotorN2, OUTPUT);

  // PWM speed pins
  pinMode(config::pins::kMotorM_PWM, OUTPUT);
  pinMode(config::pins::kMotorN_PWM, OUTPUT);

  StopAll();
}

void MotorController::SetMovement(Direction dir, uint8_t speed) {
  current_speed_ = speed;
  switch (dir) {
    case Direction::kForward:
      MoveForward(speed);
      break;
    case Direction::kReverse:
      MoveReverse(speed);
      break;
    case Direction::kTurnLeft:
      TurnLeft(speed);
      break;
    case Direction::kTurnRight:
      TurnRight(speed);
      break;
    case Direction::kAlternativeAction:
      MoveAlternative(speed);
      break;
    case Direction::kStop:
    default:
      StopAll();
      break;
  }
}

void MotorController::Stop() {
  StopAll();
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------

void MotorController::MoveForward(uint8_t speed) {
  analogWrite(config::pins::kMotorM_PWM, speed);
  analogWrite(config::pins::kMotorN_PWM, speed);
  digitalWrite(config::pins::kMotorM1, HIGH);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, HIGH);
  digitalWrite(config::pins::kMotorN2, LOW);
}

void MotorController::MoveReverse(uint8_t speed) {
  analogWrite(config::pins::kMotorM_PWM, speed);
  analogWrite(config::pins::kMotorN_PWM, speed);
  digitalWrite(config::pins::kMotorM1, LOW);
  digitalWrite(config::pins::kMotorM2, HIGH);
  digitalWrite(config::pins::kMotorN1, LOW);
  digitalWrite(config::pins::kMotorN2, HIGH);
}

void MotorController::TurnLeft(uint8_t speed) {
  // Left motor reverses, right motor forward → spins left in place.
  analogWrite(config::pins::kMotorM_PWM, speed);
  analogWrite(config::pins::kMotorN_PWM, speed);
  digitalWrite(config::pins::kMotorM1, LOW);
  digitalWrite(config::pins::kMotorM2, HIGH);
  digitalWrite(config::pins::kMotorN1, HIGH);
  digitalWrite(config::pins::kMotorN2, LOW);
}

void MotorController::TurnRight(uint8_t speed) {
  // Right motor reverses, left motor forward → spins right in place.
  analogWrite(config::pins::kMotorM_PWM, speed);
  analogWrite(config::pins::kMotorN_PWM, speed);
  digitalWrite(config::pins::kMotorM1, HIGH);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, LOW);
  digitalWrite(config::pins::kMotorN2, HIGH);
}

void MotorController::MoveAlternative(uint8_t speed) {
  // Original IR-obstacle maneuver: clockwise differential (right-biased turn)
  analogWrite(config::pins::kMotorM_PWM, speed);
  analogWrite(config::pins::kMotorN_PWM, speed);
  digitalWrite(config::pins::kMotorM1, HIGH);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, LOW);
  digitalWrite(config::pins::kMotorN2, HIGH);
}

void MotorController::StopAll() {
  analogWrite(config::pins::kMotorM_PWM, 0);
  analogWrite(config::pins::kMotorN_PWM, 0);
  digitalWrite(config::pins::kMotorM1, LOW);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, LOW);
  digitalWrite(config::pins::kMotorN2, LOW);
}
