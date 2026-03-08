#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "ColorSensor.h"
#include "MotorController.h"
#include "IrSensor.h"
#include "Telemetry.h"

// ---------------------------------------------------------------------------
// App – top-level application class.
//
// State machine:
//   kStopped  (Red)    → motors idle
//   kCaution  (Yellow) → motors run at reduced speed
//   kRunning  (Green)  → motors run at full speed; IR obstacle avoidance active
// ---------------------------------------------------------------------------
class App {
 public:
  enum class State {
    kStopped,
    kCaution,
    kRunning
  };

  App();
  void Initialize();
  void Update();

  // Exposed for testing.
  State GetState() const { return current_state_; }

 private:
  ColorSensor      color_sensor_;
  MotorController  motor_controller_;
  IrSensor         ir_sensor_;
  State            current_state_;

  void HandleStateTransitions(ColorSensor::DetectedColor color);
  void ExecuteStateActions(bool obstacle);
  void SetupPseudoPower();
};

#endif  // SRC_APP_H_
