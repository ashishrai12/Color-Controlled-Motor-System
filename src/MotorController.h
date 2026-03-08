#ifndef SRC_MOTORCONTROLLER_H_
#define SRC_MOTORCONTROLLER_H_

#include <Arduino.h>
#include "../include/Constants.h"

class MotorController {
 public:
  enum class Direction {
    kForward,
    kReverse,
    kTurnLeft,          // spin: left motor back, right forward
    kTurnRight,         // spin: right motor back, left forward
    kAlternativeAction, // IR-obstacle side-step maneuver
    kStop
  };

  MotorController();
  void Initialize();

  // Set movement direction at a given PWM speed (0-255).
  void SetMovement(Direction dir, uint8_t speed = config::speed::kFull);

  // Convenience: stop both motors immediately.
  void Stop();

 private:
  uint8_t current_speed_;

  void MoveForward(uint8_t speed);
  void MoveReverse(uint8_t speed);
  void TurnLeft(uint8_t speed);
  void TurnRight(uint8_t speed);
  void MoveAlternative(uint8_t speed);
  void StopAll();
};

#endif  // SRC_MOTORCONTROLLER_H_
