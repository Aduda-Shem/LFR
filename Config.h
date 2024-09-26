#ifndef CONFIG_H
#define CONFIG_H

// Sensor pins init
#define SENSOR_R 10
#define SENSOR_M 4
#define SENSOR_L 2

// Motor pins init
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

// Motor speed control pins (PWM-Pulse Width Modulation )
#define ENABLE_A 5
#define ENABLE_B 6

// Speed values
const int FAST_SPEED = 255;
const int MEDIUM_SPEED = 180;
const int SLOW_SPEED = 100;
// Speed when approaching corners
const int CORNER_SPEED = 150; 

// Lost line timeout in ms
const unsigned long LOST_LINE_TIMEOUT = 2000;

// PID gains for smoother control
const float KP = 2.0; 
const float KI = 0.5;
const float KD = 1.0;

#endif 
