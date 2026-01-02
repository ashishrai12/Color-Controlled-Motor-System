#include "App.h"
#include "../include/Constants.h"

App::App() : current_state_(State::kStopped) {}

void App::Initialize() {
  SetupPseudoPower();
  Telemetry::Initialize();
  color_sensor_.Initialize();
  motor_controller_.Initialize();
  ir_sensor_.Initialize();
}

void App::Update() {
  ColorSensor::RgbData rgb = color_sensor_.ReadRgb();
  bool obstacle = ir_sensor_.IsObstacleDetected();
  
  HandleStateTransitions(rgb);
  ExecuteStateActions(obstacle);

  Telemetry::Log(rgb, current_state_ == State::kRunning, obstacle);
}

void App::HandleStateTransitions(const ColorSensor::RgbData& rgb) {
  // Logic for RED detection (STOP)
  if (rgb.green > config::thresholds::kRedGreenMin && 
      rgb.green < config::thresholds::kRedGreenMax &&
      rgb.blue > config::thresholds::kRedBlueMin &&
      rgb.blue < config::thresholds::kRedBlueMax) {
    current_state_ = State::kStopped;
  }
  
  // Logic for GREEN detection (RUN)
  if (rgb.green > config::thresholds::kGreenGreenThreshold && 
      rgb.blue > config::thresholds::kGreenBlueThreshold) {
    current_state_ = State::kRunning;
  }
}

void App::ExecuteStateActions(bool obstacle) {
  if (current_state_ == State::kRunning) {
    if (obstacle) {
      motor_controller_.SetMovement(MotorController::Direction::kAlternativeAction);
      delay(config::timing::kIrActionDelayMs);
    } else {
      motor_controller_.SetMovement(MotorController::Direction::kForward);
    }
  } else {
    motor_controller_.SetMovement(MotorController::Direction::kStop);
  }
}

void App::SetupPseudoPower() {
  // Using digital pins as power/gnd sources as per original design
  pinMode(config::pins::kGnd1, OUTPUT);
  pinMode(config::pins::kGnd2, OUTPUT);
  pinMode(config::pins::kGnd3, OUTPUT);
  pinMode(config::pins::kVcc1, OUTPUT);
  pinMode(config::pins::kVcc2, OUTPUT);
  pinMode(config::pins::kVcc3, OUTPUT);

  digitalWrite(config::pins::kGnd1, LOW);
  digitalWrite(config::pins::kGnd2, LOW);
  digitalWrite(config::pins::kGnd3, LOW);
  digitalWrite(config::pins::kVcc1, HIGH);
  digitalWrite(config::pins::kVcc2, HIGH);
  digitalWrite(config::pins::kVcc3, HIGH);
}
