#ifndef SRC_APP_H_
#define SRC_APP_H_

#include "ColorSensor.h"
#include "MotorController.h"
#include "IrSensor.h"

class App {
 public:
  enum class State {
    kStopped,
    kRunning
  };

  App();
  void Initialize();
  void Update();

 private:
  ColorSensor color_sensor_;
  MotorController motor_controller_;
  IrSensor ir_sensor_;
  State current_state_;

  void HandleStateTransitions(const ColorSensor::RgbData& rgb);
  void ExecuteStateActions();
  void SetupPseudoPower();
};

#endif  // SRC_APP_H_
