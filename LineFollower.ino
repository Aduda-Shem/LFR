// Sensor init
#define sensorR 10
#define sensorM 4
#define sensorL 2

// Motor pins init
#define in1 7
#define in2 8
#define in3 9
#define in4 11

// Motor speed control pins (PWM)
// Motor A
#define enableA 5 
// Motor B
#define enableB 6 

// Customization: adjustable speeds via variables for better control
int fastSpeed = 255;      // Max speed for straight lines
int mediumSpeed = 180;    // Moderate speed for soft turns 
int slowSpeed = 100;      // Low speed for sharp turns

// Customization: time to reverse if line lost
unsigned long lostLineTimeout = 2000;
unsigned long lastLineDetectedTime;

// Function to set speed dynamically for both motors
void setMotorSpeed(int speedA, int speedB) {
  analogWrite(enableA, speedA);
  analogWrite(enableB, speedB);
}

// Function to update line recovery timeout
void setLostLineTimeout(unsigned long timeout) {
  lostLineTimeout = timeout;
}

void setup() {
  // Initialize sensor pins as input
  pinMode(sensorR, INPUT);
  pinMode(sensorM, INPUT);
  pinMode(sensorL, INPUT);

  // Initialize motor control pins as output
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Motor speed control pins (PWM)
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  // Customization: initial motor speed set dynamically
  setMotorSpeed(fastSpeed, fastSpeed);

  stopMotors();

  // Initialize timing
  lastLineDetectedTime = millis();
}

void loop() {
  // Read sensor values
  int right = digitalRead(sensorR);
  int middle = digitalRead(sensorM);
  int left = digitalRead(sensorL);

  // Customization: Adjustable timeout behavior when losing the line
  if (middle == HIGH || left == HIGH || right == HIGH) {
    // Update last time line detected
    lastLineDetectedTime = millis();
    
    if (middle == HIGH && left == LOW && right == LOW) {
      // Moving straight
      moveForward(fastSpeed);
    } 
    else if (left == HIGH && middle == LOW && right == LOW) {
      // Soft left turn
      turnLeft(mediumSpeed);
    } 
    else if (right == HIGH && middle == LOW && left == LOW) {
      // Soft right turn
      turnRight(mediumSpeed);
    } 
    else if (left == HIGH && right == HIGH && middle == LOW) {
      // Sharp corner detected
      sharpTurn(slowSpeed);
    }
  } else {
    // Determine recovery if line is lost
    if (millis() - lastLineDetectedTime > lostLineTimeout) {
      // If no line, reverse and search for line
      reverseAndSearch();
    }
  }
}

// Function to move forward 
void moveForward(int speed) {
  setMotorSpeed(speed, speed);  // Customization: reuse dynamic speed function
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to turn left 
void turnLeft(int speed) {
  setMotorSpeed(speed, speed);  // Customization: reuse dynamic speed function
  
  // Left motor stops, right motor moves forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to turn right 
void turnRight(int speed) {
  setMotorSpeed(speed, speed);  // Customization: reuse dynamic speed function
  
  // Right motor stops, left motor moves forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Function for a sharp turn 
void sharpTurn(int speed) {
  setMotorSpeed(speed, speed);  // Customization: reuse dynamic speed function
  
  // One motor moves forward, the other moves backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to reverse and search for the line
void reverseAndSearch() {
  setMotorSpeed(slowSpeed, slowSpeed);  // Customization: reuse dynamic speed function

  // Reverse both motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Reverse for 5 ms
  delay(500);
  
  // Stop and wait after reversing
  stopMotors();
  delay(200);
}

// Function to stop the motors
void stopMotors() {
  // Customization: full motor stop
  setMotorSpeed(0, 0);  // Use dynamic speed function to stop motors
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
