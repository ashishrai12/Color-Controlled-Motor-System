#ifndef SRC_MOTORCONTROLLER_H_
#define SRC_MOTORCONTROLLER_H_

#include <Arduino.h>
#include "../include/Constants.h"

class MotorController {
 public:
  enum class Direction {
    kForward,
    kAlternativeAction,  // The 'IR LOW' maneuver
    kStop
  };

  MotorController();
  void Initialize();
  void SetMovement(Direction dir);

 private:
  void MoveForward();
  void MoveAlternative();
  void StopAll();
};

#endif  // SRC_MOTORCONTROLLER_H_
