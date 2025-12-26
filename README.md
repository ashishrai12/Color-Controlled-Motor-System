Project: Color-Controlled Motor System
This project uses an Arduino to read frequency data from a TCS3200 color sensor. Based on the detected color (Red or Green), the system toggles between a Running and Stopped state. It also incorporates an IR sensor for basic navigation or obstacle detection.

<img width="654" height="670" alt="{6E22D8C9-CF66-440B-8D9A-FFAFB27D7851}" src="https://github.com/user-attachments/assets/151e0e0a-0567-4573-a791-4eb605a46eaf" />


1. Hardware Configuration
The following pins are defined in the firmware:

COMPONENT | PIN | FUNCTION
S0, S1 | 4, 5 | Output frequency scaling S2, S3 | 6, 7 | Photodiode type selection (RGB) OUT | 2 | Frequency signal input (Interrupt 0) IR Sensor | 8 | Obstacle/Path detection Motor A | 10, 11 | M1, M2 Control Motor B | 12, 13 | N1, N2 Control GND Pins | 14-16 | Digital GND for sensors VCC Pins | 17-19 | Digital VCC for sensors

2. System Logic
Color Detection
The system cycles through RGB filters to measure light frequency. It uses an Interrupt Service Routine (ISR) on Pin 2 to count pulses.

Red Filter: S2=LOW, S3=LOW

Blue Filter: S2=LOW, S3=HIGH

Green Filter: S2=HIGH, S3=HIGH

The raw frequency counts are mapped to a 0-255 scale to assist in thresholding.

Control States
STOP: If the sensor detects values matching the Red threshold, the 'running' variable is set to 0, and all motor pins are set to LOW.

START: If the sensor detects values matching the Green threshold, the 'running' variable is set to 1.

IR Navigation
While in the 'running' state:

IR LOW: Motors M1/N2 HIGH (Initiates a specific turn/maneuver).

IR HIGH: Motors M1/N1 HIGH (Moves forward).

3. Installation and Use
Connect the TCS3200 and Motor Driver pins as defined in the table above.

Note that Pins 14-19 are used as power/ground pins for the sensors. Ensure your sensors do not exceed the current limit of the Arduino pins.

Open ColorS.ino in the Arduino IDE.

Upload the code to your Arduino (Uno/Nano recommended).

4. Calibration
The thresholds for Red and Green are currently hardcoded based on frequency counts. Because ambient lighting changes sensor readings, you may need to adjust these lines:

if(green>100 && green<150 && blue>80 && blue<100) // RED detection

if(green>150 && blue>105) // GREEN detection
