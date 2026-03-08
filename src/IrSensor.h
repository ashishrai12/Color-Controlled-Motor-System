#ifndef SRC_IRSENSOR_H_
#define SRC_IRSENSOR_H_

#include <Arduino.h>
#include "../include/Constants.h"

// ---------------------------------------------------------------------------
// IrSensor – digital proximity (active-LOW) sensor with software debounce.
// ---------------------------------------------------------------------------
class IrSensor {
 public:
  IrSensor();
  void Initialize();

  // Returns true when an obstacle is consistently detected after debouncing.
  bool IsObstacleDetected();

  // Returns the number of obstacle detections since last reset.
  unsigned long GetTriggerCount() const;

  // Clears the internal trigger counter.
  void ResetTriggerCount();

 private:
  bool last_state_;
  unsigned long last_change_ms_;
  unsigned long trigger_count_;

  bool ReadRaw() const;
};

#endif  // SRC_IRSENSOR_H_
