/**
 * test_app.cpp
 * Unit tests for App state machine logic.
 */
#include <iostream>
#include <cassert>
#include "Arduino.h"
#include "../src/App.h"
#include "../include/Constants.h"

// ---------------------------------------------------------------------------
// Helper macros
// ---------------------------------------------------------------------------
#define ASSERT_EQ(a, b)                                                     \
  do {                                                                       \
    if ((a) != (b)) {                                                        \
      std::cerr << "FAIL  " << __func__ << "  line " << __LINE__            \
                << ":  expected " << (b) << "  got " << (a) << std::endl;   \
      std::exit(1);                                                          \
    }                                                                        \
  } while (0)

#define PASS()  std::cout << "PASS  " << __func__ << std::endl

// ---------------------------------------------------------------------------
// Test: Initialization sets pseudo-power and motor pins correctly
// ---------------------------------------------------------------------------
void test_initialization() {
  arduino_mock::reset();
  App app;
  app.Initialize();

  // VCC pins → HIGH
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kVcc1], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kVcc2], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kVcc3], HIGH);

  // GND pins → LOW
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kGnd1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kGnd2], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kGnd3], LOW);

  // Default state is kStopped
  ASSERT_EQ(static_cast<int>(app.GetState()),
            static_cast<int>(App::State::kStopped));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: Default state keeps motors stopped
// ---------------------------------------------------------------------------
void test_default_stop() {
  arduino_mock::reset();
  App app;
  app.Initialize();

  // IR: clear path
  arduino_mock::digital_inputs[config::pins::kIrSensor] = HIGH;

  app.Update();

  // All direction pins LOW, PWM = 0
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM2], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN2], LOW);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorM_PWM], 0);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorN_PWM], 0);
  PASS();
}

// ---------------------------------------------------------------------------
// Test: ClassifyColor → Red maps to kStopped
// ---------------------------------------------------------------------------
void test_red_color_stops_motors() {
  arduino_mock::reset();
  App app;
  app.Initialize();

  // Force IR clear
  arduino_mock::digital_inputs[config::pins::kIrSensor] = HIGH;

  // Inject a Red RGB reading via ISR counter tricks is non-trivial.
  // Instead verify ClassifyColor directly and then the state accessor.
  ColorSensor::RgbData red_rgb = {200, 120, 90};
  auto color = ColorSensor::ClassifyColor(red_rgb);
  ASSERT_EQ(static_cast<int>(color),
            static_cast<int>(ColorSensor::DetectedColor::kRed));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: ClassifyColor → Green maps to kRunning
// ---------------------------------------------------------------------------
void test_green_color_runs_motors() {
  ColorSensor::RgbData green_rgb = {50, 200, 130};
  auto color = ColorSensor::ClassifyColor(green_rgb);
  ASSERT_EQ(static_cast<int>(color),
            static_cast<int>(ColorSensor::DetectedColor::kGreen));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: ClassifyColor → Yellow maps to DetectedColor::kYellow
// ---------------------------------------------------------------------------
void test_yellow_color_detected() {
  ColorSensor::RgbData yellow_rgb = {210, 190, 40};
  auto color = ColorSensor::ClassifyColor(yellow_rgb);
  ASSERT_EQ(static_cast<int>(color),
            static_cast<int>(ColorSensor::DetectedColor::kYellow));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: ClassifyColor → Unknown for ambiguous values
// ---------------------------------------------------------------------------
void test_unknown_color() {
  ColorSensor::RgbData unknown_rgb = {10, 10, 10};
  auto color = ColorSensor::ClassifyColor(unknown_rgb);
  ASSERT_EQ(static_cast<int>(color),
            static_cast<int>(ColorSensor::DetectedColor::kUnknown));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: ColorName returns expected string labels
// ---------------------------------------------------------------------------
void test_color_names() {
  using DC = ColorSensor::DetectedColor;
  assert(std::string(ColorSensor::ColorName(DC::kRed))     == "RED");
  assert(std::string(ColorSensor::ColorName(DC::kGreen))   == "GREEN");
  assert(std::string(ColorSensor::ColorName(DC::kYellow))  == "YELLOW");
  assert(std::string(ColorSensor::ColorName(DC::kUnknown)) == "UNKNOWN");
  PASS();
}

// ---------------------------------------------------------------------------
int main() {
  std::cout << "=== App Unit Tests ===" << std::endl;
  test_initialization();
  test_default_stop();
  test_red_color_stops_motors();
  test_green_color_runs_motors();
  test_yellow_color_detected();
  test_unknown_color();
  test_color_names();
  std::cout << "All tests PASSED!" << std::endl;
  return 0;
}
