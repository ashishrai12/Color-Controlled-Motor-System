#include "IrSensor.h"

IrSensor::IrSensor() {}

void IrSensor::Initialize() {
  pinMode(config::pins::kIrSensor, INPUT);
}

bool IrSensor::IsObstacleDetected() {
  return digitalRead(config::pins::kIrSensor) == LOW;
}
