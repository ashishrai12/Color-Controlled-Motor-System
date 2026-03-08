#ifndef SRC_COLORSENSOR_H_
#define SRC_COLORSENSOR_H_

#include <Arduino.h>
#include "../include/Constants.h"

class ColorSensor {
 public:
  // -------------------------------------------------------------------------
  // Raw RGB reading (each channel mapped to 0-255)
  // -------------------------------------------------------------------------
  struct RgbData {
    int red;
    int green;
    int blue;
  };

  // -------------------------------------------------------------------------
  // Classified color result
  // -------------------------------------------------------------------------
  enum class DetectedColor {
    kUnknown,
    kRed,
    kGreen,
    kYellow
  };

  ColorSensor();
  void Initialize();

  // Returns raw, normalized RGB values.
  RgbData ReadRgb();

  // Returns a high-level classified color from the raw reading.
  static DetectedColor ClassifyColor(const RgbData& rgb);

  // Returns a human-readable label for a DetectedColor value.
  static const char* ColorName(DetectedColor color);

  // ISR entry point – must be public for attachInterrupt().
  static void HandlePulse();

 private:
  static volatile int pulse_counter_;

  void SetFilterRed();
  void SetFilterGreen();
  void SetFilterBlue();
  int  MeasureFrequency();
};

#endif  // SRC_COLORSENSOR_H_
