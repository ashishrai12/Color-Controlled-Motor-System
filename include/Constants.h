#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <Arduino.h>

namespace config {

// ---------------------------------------------------------------------------
// Pin Assignments
// ---------------------------------------------------------------------------
namespace pins {
// TCS3200 Color Sensor
constexpr int kSensorS0 = 4;
constexpr int kSensorS1 = 5;
constexpr int kSensorS2 = 6;
constexpr int kSensorS3 = 7;
constexpr int kSensorOut = 2;  // Hardware interrupt pin

// IR Proximity Sensor
constexpr int kIrSensor  = 8;

// Motor A (Left)  – PWM on pin 9, direction on 10
constexpr int kMotorM_PWM = 9;
constexpr int kMotorM1    = 10;
constexpr int kMotorM2    = 11;

// Motor B (Right) – PWM on pin 3, direction on 12
constexpr int kMotorN_PWM = 3;
constexpr int kMotorN1    = 12;
constexpr int kMotorN2    = 13;

// Pseudo-Power Pins (digital pins used as VCC / GND rails for sensors)
constexpr int kGnd1 = 14;
constexpr int kGnd2 = 15;
constexpr int kGnd3 = 16;
constexpr int kVcc1 = 17;
constexpr int kVcc2 = 18;
constexpr int kVcc3 = 19;
}  // namespace pins

// ---------------------------------------------------------------------------
// Color-Detection Thresholds  (normalized 0-255 range after mapping)
// ---------------------------------------------------------------------------
namespace thresholds {
// --- Red band ---
constexpr int kRedGreenMin = 100;
constexpr int kRedGreenMax = 150;
constexpr int kRedBlueMin = 80;
constexpr int kRedBlueMax = 100;

// --- Green band ---
constexpr int kGreenGreenThreshold = 150;
constexpr int kGreenBlueThreshold = 105;

// --- Yellow band (green+red dominant, low blue) ---
constexpr int kYellowRedMin = 180;
constexpr int kYellowGreenMin = 160;
constexpr int kYellowBlueMax = 80;
}  // namespace thresholds

// ---------------------------------------------------------------------------
// Motor Speed  (PWM duty cycle, 0-255)
// ---------------------------------------------------------------------------
namespace speed {
constexpr uint8_t kFull = 255;
constexpr uint8_t kSlow = 140;  // used during Yellow / caution state
constexpr uint8_t kStopped = 0;
}  // namespace speed

// ---------------------------------------------------------------------------
// Timing
// ---------------------------------------------------------------------------
namespace timing {
constexpr unsigned long kSensorReadDelayMs = 2;
constexpr unsigned long kIrActionDelayMs = 10;
constexpr unsigned long kIrDebounceMs = 5;  // debounce window for IR
constexpr long kSerialBaudRate = 115200;
}  // namespace timing

}  // namespace config

#endif  // INCLUDE_CONSTANTS_H_
