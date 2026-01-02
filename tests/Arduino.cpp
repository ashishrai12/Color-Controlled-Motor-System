#include "Arduino.h"

namespace arduino_mock {
std::map<int, int> pin_modes;
std::map<int, int> digital_outputs;
std::map<int, int> digital_inputs;
std::vector<void (*)()> interrupts;

void reset() {
    pin_modes.clear();
    digital_outputs.clear();
    digital_inputs.clear();
    interrupts.clear();
}
}

MockSerial Serial;
