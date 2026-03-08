/**
 * test_sensor.cpp
 * Unit tests for ColorSensor logic (classify + normalize).
 */
#include <iostream>
#include <cassert>
#include <string>
#include "Arduino.h"
#include "../src/ColorSensor.h"

#define ASSERT_EQ(a, b)                                                    \
  do {                                                                      \
    if ((a) != (b)) {                                                       \
      std::cerr << "FAIL  " << __func__ << "  line " << __LINE__           \
                << ":  expected " << (b) << "  got " << (a) << std::endl;  \
      std::exit(1);                                                         \
    }                                                                       \
  } while (0)

#define PASS()  std::cout << "PASS  " << __func__ << std::endl

using DC = ColorSensor::DetectedColor;

// ---------------------------------------------------------------------------
// Test: Red classification boundary values
// ---------------------------------------------------------------------------
void test_classify_red_boundary() {
  // Exactly at the minimum boundary for Red
  ColorSensor::RgbData rgb = {
    200,
    config::thresholds::kRedGreenMin,
    config::thresholds::kRedBlueMin
  };
  auto c = ColorSensor::ClassifyColor(rgb);
  // Must not be Yellow (red.green < kYellowGreenMin = 160)
  // Must be Red
  ASSERT_EQ(static_cast<int>(c), static_cast<int>(DC::kRed));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: Green threshold boundary
// ---------------------------------------------------------------------------
void test_classify_green_boundary() {
  ColorSensor::RgbData rgb = {
    0,
    config::thresholds::kGreenGreenThreshold,
    config::thresholds::kGreenBlueThreshold
  };
  auto c = ColorSensor::ClassifyColor(rgb);
  ASSERT_EQ(static_cast<int>(c), static_cast<int>(DC::kGreen));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: Yellow takes priority over Red and Green when criteria overlap
// ---------------------------------------------------------------------------
void test_classify_yellow_priority() {
  // High red + high green + low blue → Yellow wins
  ColorSensor::RgbData rgb = {
    config::thresholds::kYellowRedMin + 5,
    config::thresholds::kYellowGreenMin + 5,
    config::thresholds::kYellowBlueMax - 5
  };
  auto c = ColorSensor::ClassifyColor(rgb);
  ASSERT_EQ(static_cast<int>(c), static_cast<int>(DC::kYellow));
  PASS();
}

// ---------------------------------------------------------------------------
// Test: map() normalisation – verify the map() helper is correct
// ---------------------------------------------------------------------------
void test_map_helper() {
  // map(128, 0, 255, 0, 255) == 128
  long result = map(128, 0, 255, 0, 255);
  ASSERT_EQ(result, 128L);

  // map(255, 0, 255, 0, 100) == 100
  result = map(255, 0, 255, 0, 100);
  ASSERT_EQ(result, 100L);

  // map(0, 0, 255, 0, 255) == 0
  result = map(0, 0, 255, 0, 255);
  ASSERT_EQ(result, 0L);
  PASS();
}

// ---------------------------------------------------------------------------
// Test: All DetectedColor labels
// ---------------------------------------------------------------------------
void test_all_color_labels() {
  ASSERT_EQ(std::string(ColorSensor::ColorName(DC::kRed)),     std::string("RED"));
  ASSERT_EQ(std::string(ColorSensor::ColorName(DC::kGreen)),   std::string("GREEN"));
  ASSERT_EQ(std::string(ColorSensor::ColorName(DC::kYellow)),  std::string("YELLOW"));
  ASSERT_EQ(std::string(ColorSensor::ColorName(DC::kUnknown)), std::string("UNKNOWN"));
  PASS();
}

// ---------------------------------------------------------------------------
int main() {
  std::cout << "=== Sensor Unit Tests ===" << std::endl;
  test_classify_red_boundary();
  test_classify_green_boundary();
  test_classify_yellow_priority();
  test_map_helper();
  test_all_color_labels();
  std::cout << "All tests PASSED!" << std::endl;
  return 0;
}
