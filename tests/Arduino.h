#ifndef TESTS_MOCKS_ARDUINO_H_
#define TESTS_MOCKS_ARDUINO_H_

#include <stdint.h>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------
// Arduino Constants
// ---------------------------------------------------------------------------
#define OUTPUT  0x1
#define INPUT   0x0
#define HIGH    0x1
#define LOW     0x0
#define CHANGE  0x1

// ---------------------------------------------------------------------------
// Mock Arduino Global State
// ---------------------------------------------------------------------------
namespace arduino_mock {

extern std::map<int, int>       pin_modes;
extern std::map<int, int>       digital_outputs;
extern std::map<int, int>       digital_inputs;
extern std::map<int, uint8_t>   analog_outputs;   // PWM values
extern std::vector<void (*)()>  interrupts;
extern unsigned long             mock_millis;      // controllable clock

void reset();

}  // namespace arduino_mock

// ---------------------------------------------------------------------------
// Arduino API – stub implementations
// ---------------------------------------------------------------------------
inline void     pinMode(int pin, int mode)           { arduino_mock::pin_modes[pin]      = mode; }
inline void     digitalWrite(int pin, int val)       { arduino_mock::digital_outputs[pin] = val; }
inline int      digitalRead(int pin)                 { return arduino_mock::digital_inputs[pin]; }
inline void     analogWrite(int pin, uint8_t val)    { arduino_mock::analog_outputs[pin]  = val; }
inline void     delay(unsigned long ms)              { arduino_mock::mock_millis += ms; }
inline unsigned long millis()                        { return arduino_mock::mock_millis; }
inline int      digitalPinToInterrupt(int pin)       { return pin; }
inline void     attachInterrupt(int /*interrupt*/, void (*fn)(), int /*mode*/) {
  arduino_mock::interrupts.push_back(fn);
}

// ---------------------------------------------------------------------------
// Mock Serial
// ---------------------------------------------------------------------------
class MockSerial {
 public:
  void begin(long /*baud*/) {}
  template<typename T> void print(T)   {}
  template<typename T> void println(T) {}
};
extern MockSerial Serial;

// ---------------------------------------------------------------------------
// Arduino Math helpers
// ---------------------------------------------------------------------------
#undef max
#undef min
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  if (in_max == in_min) return out_min;
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif  // TESTS_MOCKS_ARDUINO_H_
