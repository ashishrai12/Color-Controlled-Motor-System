#ifndef TESTS_MOCKS_ARDUINO_H_
#define TESTS_MOCKS_ARDUINO_H_

#include <stdint.h>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

// Arduino Constants
#define OUTPUT 0x1
#define INPUT 0x0
#define HIGH 0x1
#define LOW 0x0
#define CHANGE 0x1

// Mock Arduino Global State
namespace arduino_mock {
extern std::map<int, int> pin_modes;
extern std::map<int, int> digital_outputs;
extern std::map<int, int> digital_inputs;
extern std::vector<void (*)()> interrupts;

void reset();
}

// Arduino API Functions
inline void pinMode(int pin, int mode) { arduino_mock::pin_modes[pin] = mode; }
inline void digitalWrite(int pin, int val) { arduino_mock::digital_outputs[pin] = val; }
inline int digitalRead(int pin) { return arduino_mock::digital_inputs[pin]; }
inline void delay(unsigned long ms) { /* No-op for host tests */ }
inline int digitalPinToInterrupt(int pin) { return pin; }
inline void attachInterrupt(int interrupt, void (*userFunc)(), int mode) { 
    arduino_mock::interrupts.push_back(userFunc); 
}

// Arduino Math
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif  // TESTS_MOCKS_ARDUINO_H_
