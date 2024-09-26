# LFR

This project is an LFR using an Arduino. It reads from three sensors (left, middle, and right) to detect the position of a black line on the ground. Depending on the sensor input, the robot adjusts its motor control to follow the line. If the robot loses the line, it enters a recovery mode to search for the line.

## Features

- **Straight Movement**: Moves forward when the middle sensor detects the line.
- **Soft Turns**: Turns softly based on left or right sensor input.
- **Sharp Turns**: Makes sharp turns when both left and right sensors detect the line.
- **Line Recovery**: If no line is detected for 2 seconds, it reverses to search for the line.

## Components

- **Sensors**: 
  - 3 line sensors (Right: Pin 10, Middle: Pin 4, Left: Pin 2)
  
- **Motors**:
  - Motor A (Pins: in1 - 7, in2 - 8, PWM: enableA - 5)
  - Motor B (Pins: in3 - 9, in4 - 11, PWM: enableB - 6)

## Motor Speed Control

- **Fast Speed**: Straight movement (`255` PWM)
- **Medium Speed**: Soft turns (`180` PWM)
- **Slow Speed**: Sharp turns or recovery (`100` PWM)

## Code Structure

1. **Initialization**:
    - Set sensor pins as input.
    - Set motor pins as output and stop motors.

2. **Main Loop**:
    - Continuously read sensor values to control movement.

3. **Line Following Logic**:
    - **Forward**: Middle sensor detects line.
    - **Left Turn**: Only left sensor detects line.
    - **Right Turn**: Only right sensor detects line.
    - **Sharp Turn**: Both left and right sensors detect line.

4. **Recovery Mode**:
    - If no line detected for 2 seconds, reverse to search for the line.

## Functions

- **moveForward(speed)**: Moves forward at specified speed.
- **turnLeft(speed)**: Executes a soft left turn.
- **turnRight(speed)**: Executes a soft right turn.
- **sharpTurn(speed)**: Executes a sharp turn.
- **reverseAndSearch()**: Reverses to find the line.
- **stopMotors()**: Stops all motors.