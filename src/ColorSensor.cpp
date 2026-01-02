#include "ColorSensor.h"

volatile int ColorSensor::pulse_counter_ = 0;

ColorSensor::ColorSensor() {}

void ColorSensor::Initialize() {
  pinMode(config::pins::kSensorS0, OUTPUT);
  pinMode(config::pins::kSensorS1, OUTPUT);
  pinMode(config::pins::kSensorS2, OUTPUT);
  pinMode(config::pins::kSensorS3, OUTPUT);
  pinMode(config::pins::kSensorOut, INPUT);

  // Set frequency scaling to 100%
  digitalWrite(config::pins::kSensorS0, HIGH);
  digitalWrite(config::pins::kSensorS1, HIGH);

  // Set initial filter to something stable
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

  // Mapping logic as per original .ino
  int max_val = max(data.red, max(data.blue, data.green));
  if (max_val > 0) {
    data.red = map(data.red, 0, max_val, 0, 255);
    data.green = map(data.green, 0, max_val, 0, 255);
    data.blue = map(data.blue, 0, max_val, 0, 255);
  }

  return data;
}

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
