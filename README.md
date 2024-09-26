# Line-Following Robot

This project is a simple line-following robot using an Arduino. It reads from three sensors (left, middle, and right) to detect the position of a black line on the ground. Depending on the sensor input, the robot adjusts its motor control to follow the line. If the robot loses the line, it enters a recovery mode to search for the line.

## Features

- **Straight Movement**: The robot moves forward when the middle sensor detects the line.
- **Soft Turns**: The robot makes soft turns when the left or right sensors detect the line.
- **Sharp Turns**: The robot makes sharp turns if both the left and right sensors detect the line simultaneously.
- **Line Recovery**: If the robot loses the line for more than 2 seconds, it reverses and searches for the line again.
  
## Components

- **Sensors**: 
  - 3 line sensors (Right: Pin 10, Middle: Pin 4, Left: Pin 2)
  
- **Motors**:
  - Motor A (Pins: in1 - 7, in2 - 8, PWM: enableA - 5)
  - Motor B (Pins: in3 - 9, in4 - 11, PWM: enableB - 6)

## Motor Speed Control

- **Fast Speed**: Used for straight-line movement (`255` PWM)
- **Medium Speed**: Used for soft turns (`180` PWM)
- **Slow Speed**: Used for sharp turns or line recovery (`100` PWM)

## Code Structure

1. **Initialization**:
    - Sensors are initialized as input pins.
    - Motor control pins are set as output.
    - Motors are initially stopped.

2. **Main Loop**:
    - The robot reads sensor values continuously.
    - Based on the sensor input, the robot moves forward, makes turns, or initiates line recovery.
    
3. **Line Following**:
    - **Move Forward**: If the middle sensor detects the line.
    - **Turn Left**: If only the left sensor detects the line.
    - **Turn Right**: If only the right sensor detects the line.
    - **Sharp Turn**: If both left and right sensors detect the line.

4. **Line Recovery**:
    - If no sensor detects the line for more than 2 seconds, the robot reverses and searches for the line.

## Functions

- **moveForward(speed)**: Moves the robot forward with the specified speed.
- **turnLeft(speed)**: Makes a soft left turn.
- **turnRight(speed)**: Makes a soft right turn.
- **sharpTurn(speed)**: Makes a sharp turn.
- **reverseAndSearch()**: Reverses the robot and attempts to find the line again.
- **stopMotors()**: Stops the robot by disabling all motor outputs.

## Usage

1. Upload the code to your Arduino board.
2. Connect the sensors and motors to the specified pins.
3. Place the robot on a surface with a clear black line for the sensors to detect.
4. Power the robot, and it will begin to follow the line.
