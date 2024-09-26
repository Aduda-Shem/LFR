#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

/**
 *  adjusting the proportional, integral, and derivative gains, 
 *  one can tailor the controller's response to achieve desired 
 *  performance( fundamental tools in control theory and engineering)
 */
class PIDController {
  float kp;                // Proportional gain
  float ki;                // Integral gain
  float kd;                // Derivative gain
  float integral;          // Integral term
  float previousError;     // Previous error

public:
  PIDController(float p, float i, float d) : kp(p), ki(i), kd(d), integral(0), previousError(0) {}

  float compute(float setpoint, float measuredValue) {
    float error = setpoint - measuredValue;
    integral += error;
    float derivative = error - previousError;

    // Compute the PID output
    float output = (kp * error) + (ki * integral) + (kd * derivative);

    previousError = error;

    return output;
  }

  void reset() {
    integral = 0;
    previousError = 0;
  }
};

#endif 