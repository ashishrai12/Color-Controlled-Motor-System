/**
 * Color-Controlled Motor System
 * 
 * A professional refactor of the color-controlled motor system.
 * This project uses a modular architecture with a state machine pattern.
 */

#include "src/App.h"

App system_app;

void setup() {
  // Initialize the application components
  system_app.Initialize();
}

void loop() {
  // Update the state machine and hardware interactions
  system_app.Update();
}