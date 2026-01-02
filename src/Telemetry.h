#ifndef SRC_TELEMETRY_H_
#define SRC_TELEMETRY_H_

#include <Arduino.h>
#include "ColorSensor.h"

class Telemetry {
 public:
  static void Initialize(long baud_rate = 115200);
  static void Log(const ColorSensor::RgbData& rgb, bool is_running, bool obstacle);
};

#endif  // SRC_TELEMETRY_H_
