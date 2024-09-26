#ifndef MOTOR_H
#define MOTOR_H

#include "Config.h"

class Motor {
public:
  Motor() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENABLE_A, OUTPUT);
    pinMode(ENABLE_B, OUTPUT);
  }

  void setSpeed(int speedA, int speedB) {
    analogWrite(ENABLE_A, speedA);
    analogWrite(ENABLE_B, speedB);
  }

  void stop() {
    setSpeed(0, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  // Move forward with max speed
  void moveForward(int speed = FAST_SPEED) {
    setSpeed(speed, speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  // Sharp and efficient turning for quick response
  void turnLeft(int speed) {
    setSpeed(speed, speed / 2);  // Turn with differential speed
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  void turnRight(int speed) {
    setSpeed(speed / 2, speed);  // Differential speed for smoother turns
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  // A quick recovery move when losing the line
  void quickSearch() {
    setSpeed(SLOW_SPEED, MEDIUM_SPEED);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
};

#endif 
