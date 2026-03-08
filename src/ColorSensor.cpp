#include "ColorSensor.h"

volatile int ColorSensor::pulse_counter_ = 0;

ColorSensor::ColorSensor() {}

void ColorSensor::Initialize() {
  pinMode(config::pins::kSensorS0, OUTPUT);
  pinMode(config::pins::kSensorS1, OUTPUT);
  pinMode(config::pins::kSensorS2, OUTPUT);
  pinMode(config::pins::kSensorS3, OUTPUT);
  pinMode(config::pins::kSensorOut, INPUT);

  // Set frequency scaling to 100% (S0=HIGH, S1=HIGH)
  digitalWrite(config::pins::kSensorS0, HIGH);
  digitalWrite(config::pins::kSensorS1, HIGH);

  // Park the filter on RED so the first reading is stable
  SetFilterRed();

  attachInterrupt(digitalPinToInterrupt(config::pins::kSensorOut),
                  ColorSensor::HandlePulse, CHANGE);
}

ColorSensor::RgbData ColorSensor::ReadRgb() {
  RgbData data;

  SetFilterGreen();
  data.green = MeasureFrequency();

  SetFilterBlue();
  data.blue = MeasureFrequency();

  SetFilterRed();
  data.red = MeasureFrequency();

  // Normalize each channel relative to the dominant channel (0-255 range).
  int max_val = max(data.red, max(data.blue, data.green));
  if (max_val > 0) {
    data.red   = map(data.red,   0, max_val, 0, 255);
    data.green = map(data.green, 0, max_val, 0, 255);
    data.blue  = map(data.blue,  0, max_val, 0, 255);
  }

  return data;
}

// static
ColorSensor::DetectedColor ColorSensor::ClassifyColor(const RgbData& rgb) {
  using namespace config::thresholds;

  // Yellow: high red + high green, low blue
  if (rgb.red   >= kYellowRedMin   &&
      rgb.green >= kYellowGreenMin &&
      rgb.blue  <= kYellowBlueMax) {
    return DetectedColor::kYellow;
  }

  // Red: green in [100,150] and blue in [80,100]
  if (rgb.green >= kRedGreenMin && rgb.green <= kRedGreenMax &&
      rgb.blue  >= kRedBlueMin  && rgb.blue  <= kRedBlueMax) {
    return DetectedColor::kRed;
  }

  // Green: strong green channel, moderate blue
  if (rgb.green >= kGreenGreenThreshold &&
      rgb.blue  >= kGreenBlueThreshold) {
    return DetectedColor::kGreen;
  }

  return DetectedColor::kUnknown;
}

// static
const char* ColorSensor::ColorName(DetectedColor color) {
  switch (color) {
    case DetectedColor::kRed:    return "RED";
    case DetectedColor::kGreen:  return "GREEN";
    case DetectedColor::kYellow: return "YELLOW";
    default:                     return "UNKNOWN";
  }
}

// static  (ISR)
void ColorSensor::HandlePulse() {
  pulse_counter_++;
}

void ColorSensor::SetFilterRed() {
  digitalWrite(config::pins::kSensorS2, LOW);
  digitalWrite(config::pins::kSensorS3, LOW);
}

void ColorSensor::SetFilterGreen() {
  digitalWrite(config::pins::kSensorS2, HIGH);
  digitalWrite(config::pins::kSensorS3, HIGH);
}

void ColorSensor::SetFilterBlue() {
  digitalWrite(config::pins::kSensorS2, LOW);
  digitalWrite(config::pins::kSensorS3, HIGH);
}

int ColorSensor::MeasureFrequency() {
  pulse_counter_ = 0;
  delay(config::timing::kSensorReadDelayMs);
  return pulse_counter_;
}
