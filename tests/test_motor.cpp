/**
 * test_motor.cpp
 * Unit tests for MotorController PWM and direction logic.
 */
#include <iostream>
#include <cassert>
#include "Arduino.h"
#include "../src/MotorController.h"

#define ASSERT_EQ(a, b)                                                    \
  do {                                                                      \
    if ((a) != (b)) {                                                       \
      std::cerr << "FAIL  " << __func__ << "  line " << __LINE__           \
                << ":  expected " << (int)(b) << "  got " << (int)(a) << std::endl; \
      std::exit(1);                                                         \
    }                                                                       \
  } while (0)

#define PASS()  std::cout << "PASS  " << __func__ << std::endl

// ---------------------------------------------------------------------------
void test_motor_forward_full_speed() {
  arduino_mock::reset();
  MotorController mc;
  mc.Initialize();
  mc.SetMovement(MotorController::Direction::kForward, config::speed::kFull);

  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM1], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM2], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN1], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN2], LOW);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorM_PWM], config::speed::kFull);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorN_PWM], config::speed::kFull);
  PASS();
}

// ---------------------------------------------------------------------------
void test_motor_forward_slow_speed() {
  arduino_mock::reset();
  MotorController mc;
  mc.Initialize();
  mc.SetMovement(MotorController::Direction::kForward, config::speed::kSlow);

  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorM_PWM], config::speed::kSlow);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorN_PWM], config::speed::kSlow);
  PASS();
}

// ---------------------------------------------------------------------------
void test_motor_reverse() {
  arduino_mock::reset();
  MotorController mc;
  mc.Initialize();
  mc.SetMovement(MotorController::Direction::kReverse, config::speed::kFull);

  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM2], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN2], HIGH);
  PASS();
}

// ---------------------------------------------------------------------------
void test_motor_turn_left() {
  arduino_mock::reset();
  MotorController mc;
  mc.Initialize();
  mc.SetMovement(MotorController::Direction::kTurnLeft, config::speed::kFull);

  // Left (M) motor → reverse, Right (N) motor → forward
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM2], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN1], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN2], LOW);
  PASS();
}

// ---------------------------------------------------------------------------
void test_motor_turn_right() {
  arduino_mock::reset();
  MotorController mc;
  mc.Initialize();
  mc.SetMovement(MotorController::Direction::kTurnRight, config::speed::kFull);

  // Left (M) motor → forward, Right (N) motor → reverse
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM1], HIGH);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM2], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN2], HIGH);
  PASS();
}

// ---------------------------------------------------------------------------
void test_motor_stop() {
  arduino_mock::reset();
  MotorController mc;
  mc.Initialize();

  // Set forward, then stop
  mc.SetMovement(MotorController::Direction::kForward, config::speed::kFull);
  mc.Stop();

  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorM2], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN1], LOW);
  ASSERT_EQ(arduino_mock::digital_outputs[config::pins::kMotorN2], LOW);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorM_PWM], 0);
  ASSERT_EQ(arduino_mock::analog_outputs[config::pins::kMotorN_PWM], 0);
  PASS();
}

// ---------------------------------------------------------------------------
int main() {
  std::cout << "=== Motor Unit Tests ===" << std::endl;
  test_motor_forward_full_speed();
  test_motor_forward_slow_speed();
  test_motor_reverse();
  test_motor_turn_left();
  test_motor_turn_right();
  test_motor_stop();
  std::cout << "All tests PASSED!" << std::endl;
  return 0;
}
