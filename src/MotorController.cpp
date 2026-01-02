#include "MotorController.h"

MotorController::MotorController() {}

void MotorController::Initialize() {
  pinMode(config::pins::kMotorM1, OUTPUT);
  pinMode(config::pins::kMotorM2, OUTPUT);
  pinMode(config::pins::kMotorN1, OUTPUT);
  pinMode(config::pins::kMotorN2, OUTPUT);
  StopAll();
}

void MotorController::SetMovement(Direction dir) {
  switch (dir) {
    case Direction::kForward:
      MoveForward();
      break;
    case Direction::kAlternativeAction:
      MoveAlternative();
      break;
    case Direction::kStop:
    default:
      StopAll();
      break;
  }
}

void MotorController::MoveForward() {
  digitalWrite(config::pins::kMotorM1, HIGH);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, HIGH);
  digitalWrite(config::pins::kMotorN2, LOW);
}

void MotorController::MoveAlternative() {
  digitalWrite(config::pins::kMotorM1, HIGH);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, LOW);
  digitalWrite(config::pins::kMotorN2, HIGH);
  // Note: The original code had a delay(10) inside the IR branch.
  // We'll handle timing in the state machine or application logic to keep
  // this class non-blocking where possible.
}

void MotorController::StopAll() {
  digitalWrite(config::pins::kMotorM1, LOW);
  digitalWrite(config::pins::kMotorM2, LOW);
  digitalWrite(config::pins::kMotorN1, LOW);
  digitalWrite(config::pins::kMotorN2, LOW);
}
