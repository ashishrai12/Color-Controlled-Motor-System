#!/usr/bin/env python3
"""
Color-Controlled Motor System - Logic Simulator (Python)

This script simulates the decision-making logic of the C++ App class.
It allows testing behavior by piping or manually inputting color/sensor states.
"""

import sys
import time
from enum import Enum
from dataclasses import dataclass

class State(Enum):
    STOPPED = 0
    CAUTION = 1
    RUNNING = 2

class Color(Enum):
    UNKNOWN = 0
    RED = 1
    GREEN = 2
    YELLOW = 3

@dataclass
class RgbData:
    red: int
    green: int
    blue: int

class RobotSimulator:
    def __init__(self):
        self.state = State.STOPPED
        self.obstacle_count = 0
        self.current_speed = 0

    def classify_color(self, r, g, b) -> Color:
        # Yellow detection (based on Constants.h thresholds)
        if r >= 180 and g >= 160 and b <= 80:
            return Color.YELLOW
        # Red detection
        if 100 <= g <= 150 and 80 <= b <= 100:
            return Color.RED
        # Green detection
        if g >= 150 and b >= 105:
            return Color.GREEN
        return Color.UNKNOWN

    def update(self, r, g, b, has_obstacle):
        color = self.classify_color(r, g, b)
        
        # State Transitions
        if color == Color.RED:
            self.state = State.STOPPED
        elif color == Color.YELLOW:
            self.state = State.CAUTION
        elif color == Color.GREEN:
            self.state = State.RUNNING

        # Action Execution
        action = "IDLE"
        if self.state == State.RUNNING:
            if has_obstacle:
                action = "SIDE-STEP MANEUVER (FULL SPEED)"
                self.current_speed = 255
                self.obstacle_count += 1
            else:
                action = "FORWARD (FULL SPEED)"
                self.current_speed = 255
        elif self.state == State.CAUTION:
            if has_obstacle:
                action = "STOP (OBSTACLE IN CAUTION ZONE)"
                self.current_speed = 0
            else:
                action = "FORWARD (SLOW SPEED)"
                self.current_speed = 140
        else:
            action = "STOP"
            self.current_speed = 0

        self.print_telemetry(r, g, b, color.name, has_obstacle, action)

    def print_telemetry(self, r, g, b, color_name, obs, action):
        print(f"\n[SIM] RGB:({r:3}, {g:3}, {b:3}) | Color: {color_name:7} | Obstacle: {'YES' if obs else 'NO '}")
        print(f"      State: {self.state.name:7} | Speed: {self.current_speed:3} | Action: {action}")

def main():
    sim = RobotSimulator()
    print("=== Robot Logic Simulator (CLI) ===")
    print("Enter mock sensor data: R G B Obstacle(0/1)")
    print("Example: '200 120 90 0' for stationary Red")
    print("Press Ctrl+C to exit.\n")

    try:
        while True:
            line = input("input > ").strip()
            if not line:
                continue
            
            parts = line.split()
            if len(parts) != 4:
                print("Error: Provide R G B and Obstacle(0 or 1)")
                continue
                
            try:
                r, g, b, obs = map(int, parts)
                sim.update(r, g, b, bool(obs))
            except ValueError:
                print("Error: Values must be integers.")
    except KeyboardInterrupt:
        print("\nSimulation ended.")

if __name__ == "__main__":
    main()
