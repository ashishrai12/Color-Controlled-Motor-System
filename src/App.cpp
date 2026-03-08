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
  const ColorSensor::RgbData        rgb      = color_sensor_.ReadRgb();
  const ColorSensor::DetectedColor  color    = ColorSensor::ClassifyColor(rgb);
  const bool                        obstacle = ir_sensor_.IsObstacleDetected();

  HandleStateTransitions(color);
  ExecuteStateActions(obstacle);

  // Emit CSV telemetry for the Serial Plotter.
  Telemetry::Log(rgb, color, current_state_ == State::kRunning, obstacle);

  // Emit JSON telemetry for structured monitoring (throttle to every N calls
  // if bandwidth is a concern – here we log every update for completeness).
  Telemetry::LogJson(rgb, color,
                     current_state_ == State::kRunning,
                     obstacle,
                     ir_sensor_.GetTriggerCount());
}

void App::HandleStateTransitions(ColorSensor::DetectedColor color) {
  switch (color) {
    case ColorSensor::DetectedColor::kRed:
      current_state_ = State::kStopped;
      break;
    case ColorSensor::DetectedColor::kYellow:
      current_state_ = State::kCaution;
      break;
    case ColorSensor::DetectedColor::kGreen:
      current_state_ = State::kRunning;
      break;
    case ColorSensor::DetectedColor::kUnknown:
    default:
      // Retain the current state when no colour is classified.
      break;
  }
}

void App::ExecuteStateActions(bool obstacle) {
  switch (current_state_) {
    case State::kRunning:
      if (obstacle) {
        motor_controller_.SetMovement(MotorController::Direction::kAlternativeAction,
                                      config::speed::kFull);
        delay(config::timing::kIrActionDelayMs);
      } else {
        motor_controller_.SetMovement(MotorController::Direction::kForward,
                                      config::speed::kFull);
      }
      break;

    case State::kCaution:
      // Slow forward movement; stop if obstacle detected.
      if (obstacle) {
        motor_controller_.Stop();
      } else {
        motor_controller_.SetMovement(MotorController::Direction::kForward,
                                      config::speed::kSlow);
      }
      break;

    case State::kStopped:
    default:
      motor_controller_.Stop();
      break;
  }
}

void App::SetupPseudoPower() {
  // Drive digital pins as GND / VCC rails for sensor modules.
  pinMode(config::pins::kGnd1, OUTPUT); digitalWrite(config::pins::kGnd1, LOW);
  pinMode(config::pins::kGnd2, OUTPUT); digitalWrite(config::pins::kGnd2, LOW);
  pinMode(config::pins::kGnd3, OUTPUT); digitalWrite(config::pins::kGnd3, LOW);
  pinMode(config::pins::kVcc1, OUTPUT); digitalWrite(config::pins::kVcc1, HIGH);
  pinMode(config::pins::kVcc2, OUTPUT); digitalWrite(config::pins::kVcc2, HIGH);
  pinMode(config::pins::kVcc3, OUTPUT); digitalWrite(config::pins::kVcc3, HIGH);
}
