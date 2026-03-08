# Robot Telemetry Visualizer

This directory contains a web-based dashboard designed to provide real-time visualization of the Color-Controlled Motor System's internal telemetry.

## Overview

The Visualizer is a lightweight, zero-install tool built with HTML, CSS, and Vanilla JavaScript. It leverages the **Web Serial API** to communicate directly with an Arduino over a USB connection, allowing users to monitor sensor data and system states without needing specialized serial plotting software or Python environments.

## Features

- **Real-time RGB Monitoring**: Displays raw values from the TCS3200 color sensor and provides a live background-color preview of what the robot "sees."
- **State Visualization**: Clear indicators for the system's finite state machine (RUNNING vs. STOPPED).
- **Obstacle Alerts**: Visual feedback when the IR sensor detects a path obstruction.
- **Performance Tracking**: Built-in telemetry frequency counter (Hz) to monitor data throughput.
- **Modern UI**: A responsive, high-contrast dark mode dashboard built for high visibility in various lighting conditions.

## Prerequisites

To use this visualizer, you need:
1. **A Supported Browser**: Google Chrome or Microsoft Edge (version 89+). 
   - *Note: Firefox and Safari do not currently support the Web Serial API.*
2. **Firmware**: Your Arduino must be flashed with the modular C++ code from this repository, which includes the `Telemetry` module.
3. **Hardware**: The Arduino must be connected to your computer via USB.

## How to Use

1. **Flash the Robot**: Ensure your Arduino has the latest firmware and is connected to your USB port.
2. **Open the Dashboard**: Open `tools/Visualizer.html` in a supported browser. You can do this by dragging the file into a browser tab.
3. **Connect**:
   - Click the **"Connect to Robot"** button at the top of the page.
   - A browser popup will appear. Select the entry corresponding to your Arduino (e.g., "Arduino Uno" or "USB Serial Port").
   - Click **Connect**.
4. **Monitor**: Once connected, the data will begin streaming automatically. The "Telemetry Hz" counter should start incrementing, and the gauges will update in real-time.

## Troubleshooting

- **"Connect" button does nothing**: Ensure you are using Chrome or Edge. Check if another program (like the Arduino Serial Monitor) is already using the COM port.
- **No data appearing**: Check your physical connections and ensure the baud rate in the code (`Telemetry.h`) matches the dashboard (default is **115200**).
- **Inaccurate Colors**: Lighting conditions significantly affect the TCS3200 sensor. You may need to calibrate the thresholds in `include/Constants.h`.

## Technical Details

The visualizer expects comma-separated key-value pairs over serial at 115200 baud, ending with a newline.
Example payload:
`Red:120,Green:45,Blue:30,Running:100,Obstacle:0\n`
