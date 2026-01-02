#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <Arduino.h>

namespace config {

// TCS3200 Color Sensor Pins
namespace pins {
constexpr int kSensorS0 = 4;
constexpr int kSensorS1 = 5;
constexpr int kSensorS2 = 6;
constexpr int kSensorS3 = 7;
constexpr int kSensorOut = 2;

// IR Sensor Pins
constexpr int kIrSensor = 8;

// Motor A Control Pins
constexpr int kMotorM1 = 10;
constexpr int kMotorM2 = 11;

// Motor B Control Pins
constexpr int kMotorN1 = 12;
constexpr int kMotorN2 = 13;

// Pseudo-Power Pins (Digital pins used as VCC/GND)
constexpr int kGnd1 = 14;
constexpr int kGnd2 = 15;
constexpr int kGnd3 = 16;
constexpr int kVcc1 = 17;
constexpr int kVcc2 = 18;
constexpr int kVcc3 = 19;
}  // namespace pins

// Thresholds and Calibration
namespace thresholds {
// Red detection thresholds
constexpr int kRedGreenMin = 100;
constexpr int kRedGreenMax = 150;
constexpr int kRedBlueMin = 80;
constexpr int kRedBlueMax = 100;

// Green detection thresholds
constexpr int kGreenGreenThreshold = 150;
constexpr int kGreenBlueThreshold = 105;
}  // namespace thresholds

// Timing
namespace timing {
constexpr unsigned long kSensorReadDelayMs = 2;
constexpr unsigned long kIrActionDelayMs = 10;
}  // namespace timing

}  // namespace config

#endif  // INCLUDE_CONSTANTS_H_
