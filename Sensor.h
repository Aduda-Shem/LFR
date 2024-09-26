#ifndef SENSOR_H
#define SENSOR_H

#include "Config.h"

class Sensor {
public:
  Sensor() {
    pinMode(SENSOR_R, INPUT);
    pinMode(SENSOR_M, INPUT);
    pinMode(SENSOR_L, INPUT);
  }

  bool isRightActive() {
    return digitalRead(SENSOR_R) == HIGH;
  }

  bool isMiddleActive() {
    return digitalRead(SENSOR_M) == HIGH;
  }

  bool isLeftActive() {
    return digitalRead(SENSOR_L) == HIGH;
  }
};

#endif
