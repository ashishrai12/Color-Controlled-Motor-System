#ifndef SRC_COLORSENSOR_H_
#define SRC_COLORSENSOR_H_

#include <Arduino.h>
#include "../include/Constants.h"

class ColorSensor {
 public:
  struct RgbData {
    int red;
    int green;
    int blue;
  };

  ColorSensor();
  void Initialize();
  RgbData ReadRgb();

  // Static method for ISR access
  static void HandlePulse();

 private:
  static volatile int pulse_counter_;
  
  void SetFilterRed();
  void SetFilterGreen();
  void SetFilterBlue();
  int MeasureFrequency();
};

#endif  // SRC_COLORSENSOR_H_
