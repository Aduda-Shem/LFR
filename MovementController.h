#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include "Motor.h"
#include "Sensor.h"
#include "PIDController.h"
#include "Config.h"

class MovementController {
  Motor motor;
  Sensor sensor;
  PIDController pid;  // Instantiate the PID controller
  const float setpoint = 1.0; // Target position for the line
  unsigned long lastLineDetectedTime;

public:
  MovementController() : pid(1.0, 0.1, 0.05) { // Initialize PID with tuning parameters
    lastLineDetectedTime = millis();
  }

  void update() {
    float position = getLinePosition(); // Get the position of the line (can be 0, 1, 2, ... for left, center, right)
    
    // Check if the line is detected
    if (position >= 0) {
      lastLineDetectedTime = millis();
      float pidOutput = pid.compute(setpoint, position); // Calculate PID output

      // Adjust speeds based on PID output
      int baseSpeed = FAST_SPEED; // Base speed for moving forward
      int leftMotorSpeed = baseSpeed - pidOutput; // Adjust left motor speed
      int rightMotorSpeed = baseSpeed + pidOutput; // Adjust right motor speed

      // Clamp motor speeds to valid range
      leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
      rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

      motor.setSpeed(leftMotorSpeed, rightMotorSpeed); // Set motor speeds
    } else {
      // If the line is lost, initiate the search
      if (millis() - lastLineDetectedTime > LOST_LINE_TIMEOUT) {
        motor.quickSearch(); // Efficient search with differential speed
      }
    }
  }

private:
  float getLinePosition() {
    // Implement logic to determine the position of the line based on sensor readings
    // For example, return 0 for left, 1 for center, and 2 for right, or any other scale based on your sensors.
    if (sensor.isMiddleActive()) {
      return 1.0; // Center position
    } else if (sensor.isLeftActive()) {
      return 0.0; // Left position
    } else if (sensor.isRightActive()) {
      return 2.0; // Right position
    }
    return -1.0; // Line not detected
  }
};

#endif // MOVEMENT_CONTROLLER_H
