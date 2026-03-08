# Auxiliary Tools and Simulation

This directory contains standalone tools to support the development, testing, and monitoring of the Color-Controlled Motor System.

## 1. Robot Simulation Illustration (`Simulation.html`)
An interactive web-based simulator designed to visualize the robot's movement logic in real-time.

- **How to use:** Open `Simulation.html` in any modern web browser.
- **Features:** 
    - Interactive buttons to inject "detected colors" (Red, Green, Yellow).
    - Obstacle toggle to trigger IR sensor behavior.
    - Canvas-based robot movement showing speed and heading changes.
    - Automated trail path to visualize maneuvers.

## 2. Logic Simulator (`LogicSim.py`)
A Python command-line tool that mirrors the C++ `App` state machine logic. Useful for verifying thresholds and actions without hardware or a browser.

- **Prerequisites:** Python 3.x
- **How to use:**
    ```bash
    python LogicSim.py
    ```
- **Input Format:** `R G B Obstacle_Flag` (e.g., `210 190 40 0` for a Yellow clear path).

## 3. Telemetry Visualizer (`Visualizer.html`)
A real-time dashboard that connects to the physical robot via the **Web Serial API**.

- **Prerequisites:** A browser that supports Web Serial (Chrome, Edge, Opera).
- **How to use:** Connect the Arduino via USB, open `Visualizer.html`, click **Connect**, and select the appropriate COM port.
- **Features:**
    - Live RGB value display.
    - Color swatch preview.
    - Status indicators for Running/Stopped and Obstacles.
    - Telemetry throughput (Hz) monitor.
