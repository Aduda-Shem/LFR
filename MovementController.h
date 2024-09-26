#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include "Motor.h"
#include "Sensor.h"
#include "PIDController.h"
#include "Config.h"

class MovementController {
  Motor motor;
  Sensor sensor;
  PIDController pid;
  // Target position for the linee
  const float setpoint = 1.0; 
  unsigned long lastLineDetectedTime;

public:
  MovementController() : pid(KP, KI, KD) {
    lastLineDetectedTime = millis();
  }

  void update() {
    // Get kine position 
    float position = getLinePosition(); 

    if (position >= 0) {
      lastLineDetectedTime = millis();
      float pidOutput = pid.compute(setpoint, position);

      // speed control based on position
      int baseSpeed = FAST_SPEED; 
      int leftMotorSpeed = baseSpeed - pidOutput;
      int rightMotorSpeed = baseSpeed + pidOutput;

      // Adjust speed based on proximity to corners
      if (position == 0.0 || position == 2.0) { 
        // edges (corners)
        leftMotorSpeed = CORNER_SPEED;
        rightMotorSpeed = CORNER_SPEED;
      } else if (position == 1.0) { 
        // Center position
        leftMotorSpeed = FAST_SPEED;
        rightMotorSpeed = FAST_SPEED;
      }

      // Clamp motor speeds to valid range
      leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
      rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

      motor.setSpeed(leftMotorSpeed, rightMotorSpeed);
    } else {
      // If the line is lost, initiate recovery
      if (millis() - lastLineDetectedTime > LOST_LINE_TIMEOUT) {
        motor.reverse(); 
        delay(300); 
        motor.quickSearch(); 
      }
    }
  }

private:
  float getLinePosition() {
    if (sensor.isMiddleActive()) {
      // Center position
      return 1.0; 
    } else if (sensor.isLeftActive()) {
      // Left position
      return 0.0; 
    } else if (sensor.isRightActive()) {
      // Right position
      return 2.0; 
    }
    // Line not detected
    return -1.0; 
  }
};

#endif 
