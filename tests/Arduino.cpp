#include "Arduino.h"

namespace arduino_mock {

std::map<int, int>       pin_modes;
std::map<int, int>       digital_outputs;
std::map<int, int>       digital_inputs;
std::map<int, uint8_t>   analog_outputs;
std::vector<void (*)()>  interrupts;
unsigned long             mock_millis = 0;

void reset() {
  pin_modes.clear();
  digital_outputs.clear();
  digital_inputs.clear();
  analog_outputs.clear();
  interrupts.clear();
  mock_millis = 0;
}

}  // namespace arduino_mock

MockSerial Serial;
