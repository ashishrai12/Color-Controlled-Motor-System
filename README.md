# Color-Controlled Motor System

## 📖 About

This system is a **behavior-driven autonomous platform** that translates environmental visual data into real-time mechanical action. It is designed to demonstrate reactive robotics logic in a modular C++ environment.

### Core Outputs
*   🔴 **Dynamic Gating:** Instantly halts all mechanical movement upon detecting a Red threshold, acting as an optical "kill switch."
*   🟢 **Autonomous Activation:** Resumes operational state when Green is identified, allowing for hands-free workflow management.
*   🛰 **Intelligent Obstacle Avoidance:** While in motion, the system utilizes IR sensing to execute pre-programmed maneuvers when land-based obstacles are detected.
*   ⚡ **Low-Latency Feedback:** Leverages hardware interrupts for frequency-to-color mapping, ensuring sub-millisecond response times to color changes.

## System Architecture

The project has been refactored from a monolithic sketch into a clean, component-based architecture following Staff Engineer standards.

### Component Diagram

```mermaid
graph TD
    Main[.ino Entry] --> App[App Class]
    App --> CS[ColorSensor]
    App --> MC[MotorController]
    App --> IR[IrSensor]
    
    subgraph Components
        CS
        MC
        IR
    end
    
    subgraph Logic
        App -- Coordinates --> SM[State Machine]
    end
```

### State Machine Logic

The system operates using a state machine to ensure predictable behavior:

| State | Condition | Action |
|-------|-----------|--------|
| **STOPPED** | Red Color Detected | Motors Idle |
| **RUNNING** | Green Color Detected | Forward or IR Maneuver |

While in the **RUNNING** state, the system performs real-time IR obstacle detection:
- **Path Clear:** Move Forward.
- **Obstacle Detected:** Execute alternative maneuver.

---

## Hardware Configuration

| Component | Pin(s) | Function |
|-----------|--------|----------|
| **TCS3200 S0-S1** | 4, 5 | Frequency Scaling |
| **TCS3200 S2-S3** | 6, 7 | Photodiode Type (RGB) |
| **TCS3200 OUT** | 2 | Frequency Input (Interrupt) |
| **IR Sensor** | 8 | Obstacle Detection |
| **Motor A** | 10, 11 | Speed/Direction Control |
| **Motor B** | 12, 13 | Speed/Direction Control |
| **Power Pins** | 14-19 | Pseudo VCC/GND for sensors |

---

## Project Structure

- `ColorS.ino`: Lightweight entry point.
- `include/Constants.h`: Centralized configuration for pins and thresholds.
- `src/App.h/.cpp`: Main application logic and state machine.
- `src/ColorSensor.h/.cpp`: Driver for the TCS3200 sensor.
- `src/MotorController.h/.cpp`: H-Bridge motor control abstraction.
- `src/IrSensor.h/.cpp`: Wrapper for the IR proximity sensor.

---

## 🚀 Build and Installation

### Prerequisites
- Arduino IDE 2.0+ or PlatformIO.
- Arduino Uno/Nano or compatible board.

### Instructions
1. Clone the repository.
2. Open `ColorS.ino` in the Arduino IDE.
3. Ensure the `src` and `include` folders are in the same parent directory as `ColorS.ino`.
4. Select your board and port.
5. Click **Upload**.

---

## Calibration and Configuration

All "magic numbers" have been removed and replaced with named constants in `include/Constants.h`. To calibrate the system for your lighting conditions, modify the values in the `config::thresholds` namespace:

```cpp
namespace thresholds {
    constexpr int kRedGreenMin = 100;
    // ... adjust as needed
}
```

## 📜 Style Guide
This project follows the **Google C++ Style Guide** adapted for embedded systems, ensuring high readability and maintainability.
