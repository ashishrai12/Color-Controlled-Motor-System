#include "Telemetry.h"

void Telemetry::Initialize(long baud_rate) {
  Serial.begin(baud_rate);
}

void Telemetry::Log(const ColorSensor::RgbData& rgb,
                    ColorSensor::DetectedColor color,
                    bool is_running,
                    bool obstacle) {
  // Format compatible with the Arduino Serial Plotter (label:value pairs).
  Serial.print("Red:");     Serial.print(rgb.red);
  Serial.print(",Green:");  Serial.print(rgb.green);
  Serial.print(",Blue:");   Serial.print(rgb.blue);
  Serial.print(",Color:");  Serial.print(ColorSensor::ColorName(color));
  Serial.print(",Running:"); Serial.print(is_running ? 100 : 0);
  Serial.print(",Obstacle:"); Serial.println(obstacle ? 50 : 0);
}

void Telemetry::LogJson(const ColorSensor::RgbData& rgb,
                        ColorSensor::DetectedColor color,
                        bool is_running,
                        bool obstacle,
                        unsigned long obstacle_count) {
  // Minimal JSON – no heap allocation (all string literals + ints).
  Serial.print("{\"r\":");         Serial.print(rgb.red);
  Serial.print(",\"g\":");         Serial.print(rgb.green);
  Serial.print(",\"b\":");         Serial.print(rgb.blue);
  Serial.print(",\"color\":\"");   Serial.print(ColorSensor::ColorName(color));
  Serial.print("\",\"running\":"); Serial.print(is_running ? 1 : 0);
  Serial.print(",\"obstacle\":"); Serial.print(obstacle ? 1 : 0);
  Serial.print(",\"obs_count\":"); Serial.print(obstacle_count);
  Serial.println("}");
}
