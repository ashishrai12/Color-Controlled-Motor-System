#ifndef SRC_IRSENSOR_H_
#define SRC_IRSENSOR_H_

#include <Arduino.h>
#include "../include/Constants.h"

class IrSensor {
 public:
  IrSensor();
  void Initialize();
  bool IsObstacleDetected(); // Returns true if LOW (sensor triggered)
};

#endif  // SRC_IRSENSOR_H_
