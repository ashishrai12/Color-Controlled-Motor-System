/**
 * test_ir.cpp
 * Unit tests for IrSensor debounce and trigger counting.
 */
#include <iostream>
#include <cassert>
#include "Arduino.h"
#include "../src/IrSensor.h"

#define ASSERT_EQ(a, b)                                                    \
  do {                                                                      \
    if ((a) != (b)) {                                                       \
      std::cerr << "FAIL  " << __func__ << "  line " << __LINE__           \
                << ":  expected " << (b) << "  got " << (a) << std::endl;  \
      std::exit(1);                                                         \
    }                                                                       \
  } while (0)

#define ASSERT_TRUE(x)   ASSERT_EQ((x), true)
#define ASSERT_FALSE(x)  ASSERT_EQ((x), false)

#define PASS()  std::cout << "PASS  " << __func__ << std::endl

// ---------------------------------------------------------------------------
// Test: Clear path (IR HIGH) is not an obstacle
// ---------------------------------------------------------------------------
void test_no_obstacle_when_high() {
  arduino_mock::reset();
  // Set before Initialize() so last_state_ is seeded correctly.
  arduino_mock::digital_inputs[config::pins::kIrSensor] = HIGH;
  IrSensor ir;
  ir.Initialize();

  ASSERT_FALSE(ir.IsObstacleDetected());
  PASS();
}

// ---------------------------------------------------------------------------
// Test: Obstacle detected after debounce window elapses
// ---------------------------------------------------------------------------
void test_obstacle_after_debounce() {
  arduino_mock::reset();
  // Start clear – seed before Initialize().
  arduino_mock::digital_inputs[config::pins::kIrSensor] = HIGH;
  IrSensor ir;
  ir.Initialize();

  ir.IsObstacleDetected();

  // Trigger obstacle, but don't advance the clock → debounce rejects it
  arduino_mock::digital_inputs[config::pins::kIrSensor] = LOW;
  ASSERT_FALSE(ir.IsObstacleDetected());

  // Advance mock clock past debounce threshold
  arduino_mock::mock_millis += config::timing::kIrDebounceMs + 1;
  ASSERT_TRUE(ir.IsObstacleDetected());

  PASS();
}

// ---------------------------------------------------------------------------
// Test: Trigger counter increments on each confirmed obstacle edge
// ---------------------------------------------------------------------------
void test_trigger_counter() {
  arduino_mock::reset();
  arduino_mock::digital_inputs[config::pins::kIrSensor] = HIGH;
  IrSensor ir;
  ir.Initialize();

  ASSERT_EQ(static_cast<int>(ir.GetTriggerCount()), 0);

  auto fire_obstacle = [&]() {
    // Start HIGH (clear)
    arduino_mock::digital_inputs[config::pins::kIrSensor] = HIGH;
    arduino_mock::mock_millis += config::timing::kIrDebounceMs + 1;
    ir.IsObstacleDetected();

    // Transition to LOW (obstacle)
    arduino_mock::digital_inputs[config::pins::kIrSensor] = LOW;
    arduino_mock::mock_millis += config::timing::kIrDebounceMs + 1;
    ir.IsObstacleDetected();
  };

  fire_obstacle();
  ASSERT_EQ(static_cast<int>(ir.GetTriggerCount()), 1);

  fire_obstacle();
  ASSERT_EQ(static_cast<int>(ir.GetTriggerCount()), 2);

  ir.ResetTriggerCount();
  ASSERT_EQ(static_cast<int>(ir.GetTriggerCount()), 0);

  PASS();
}

// ---------------------------------------------------------------------------
int main() {
  std::cout << "=== IR Sensor Unit Tests ===" << std::endl;
  test_no_obstacle_when_high();
  test_obstacle_after_debounce();
  test_trigger_counter();
  std::cout << "All tests PASSED!" << std::endl;
  return 0;
}
