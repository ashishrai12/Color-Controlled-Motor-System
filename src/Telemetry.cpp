#include "Telemetry.h"

void Telemetry::Initialize(long baud_rate) {
  Serial.begin(baud_rate);
}

void Telemetry::Log(const ColorSensor::RgbData& rgb, bool is_running, bool obstacle) {
  // Output format optimized for Arduino Serial Plotter
  Serial.print("Red:");
  Serial.print(rgb.red);
  Serial.print(",Green:");
  Serial.print(rgb.green);
  Serial.print(",Blue:");
  Serial.print(rgb.blue);
  Serial.print(",Running:");
  Serial.print(is_running ? 100 : 0); // Scaled for visibility
  Serial.print(",Obstacle:");
  Serial.println(obstacle ? 50 : 0);
}
