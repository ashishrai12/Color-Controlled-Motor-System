#include "IrSensor.h"

IrSensor::IrSensor()
    : last_state_(false),
      last_change_ms_(0),
      trigger_count_(0) {}

void IrSensor::Initialize() {
  pinMode(config::pins::kIrSensor, INPUT);
  last_state_     = ReadRaw();
  last_change_ms_ = millis();
}

bool IrSensor::IsObstacleDetected() {
  bool raw = ReadRaw();

  // Debounce: only accept state change after kIrDebounceMs has elapsed.
  if (raw != last_state_) {
    unsigned long now = millis();
    if ((now - last_change_ms_) >= config::timing::kIrDebounceMs) {
      last_state_     = raw;
      last_change_ms_ = now;
      if (raw) {
        ++trigger_count_;
      }
    }
  }

  return last_state_;
}

unsigned long IrSensor::GetTriggerCount() const {
  return trigger_count_;
}

void IrSensor::ResetTriggerCount() {
  trigger_count_ = 0;
}

bool IrSensor::ReadRaw() const {
  // Sensor is active-LOW: LOW signal means obstacle present.
  return digitalRead(config::pins::kIrSensor) == LOW;
}
