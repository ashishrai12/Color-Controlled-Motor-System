#ifndef SRC_TELEMETRY_H_
#define SRC_TELEMETRY_H_

#include <Arduino.h>
#include "ColorSensor.h"

// ---------------------------------------------------------------------------
// Telemetry – serial output helpers.
//
// Log() emits CSV/Serial-Plotter compatible lines.
// LogJson() emits machine-readable JSON for host-side tooling.
// ---------------------------------------------------------------------------
class Telemetry {
 public:
  static void Initialize(long baud_rate = config::timing::kSerialBaudRate);

  // CSV format  – optimised for the Arduino Serial Plotter.
  static void Log(const ColorSensor::RgbData& rgb,
                  ColorSensor::DetectedColor color,
                  bool is_running,
                  bool obstacle);

  // JSON format – useful for Serial Monitor / host-side dashboards.
  static void LogJson(const ColorSensor::RgbData& rgb,
                      ColorSensor::DetectedColor color,
                      bool is_running,
                      bool obstacle,
                      unsigned long obstacle_count);
};

#endif  // SRC_TELEMETRY_H_
