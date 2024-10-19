#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo7;

int pos = 100;  // Initial position for servos 1 and 3
int increment = 1;  // Step size for movement
int delayTime = 10;  // Delay in milliseconds between movements

// Variables for servo7
int servo7MinPos = 0;
int servo7MaxPos = 20;
int servo7Pos = servo7MinPos;
int servo7Increment = 1;  // Step size for servo7 movement
unsigned long previousMillis = 0;
int servo7Delay = 40;  // Time between servo7 steps

void setup() {
  servo1.attach(12);
  servo2.attach(11);
  servo3.attach(10);
  servo4.attach(9);
  servo7.attach(8);
  
  // Initial position setup
  servo1.write(pos);
  servo2.write(180 - pos);
  servo3.write(180 - pos);
  servo4.write(pos);
  servo7.write(servo7MinPos);  // Start at minimum position
}

void loop() {
  // Move servos 1 and 3 from 100 to 160 degrees, servo 2 and 4 in the opposite direction
  for (pos = 100; pos <= 160; pos += increment) {
    servo1.write(pos);          // Move servo1 to 'pos'
    servo2.write(180 - pos);    // Move servo2 to the opposite of 'pos'
    servo3.write(180 - pos);    // Move servo3 to the opposite of servo1
    servo4.write(pos);          // Move servo4 in sync with servo2
    
    moveServo7();  // Move servo7 independently
    
    delay(delayTime);  // Wait for the servos to reach the position
  }

  // Move servos 1 and 3 back from 160 to 100 degrees, servo 2 and 4 in the opposite direction
  for (pos = 160; pos >= 100; pos -= increment) {
    servo1.write(pos);          // Move servo1 to 'pos'
    servo2.write(180 - pos);    // Move servo2 to the opposite of 'pos'
    servo3.write(180 - pos);    // Move servo3 to the opposite of servo1
    servo4.write(pos);          // Move servo4 in sync with servo2

    moveServo7();  // Move servo7 independently
    
    delay(delayTime);  // Wait for the servos to reach the position
  }
}

// Function to move servo7 independently between 0° and 20°
void moveServo7() {
  unsigned long currentMillis = millis();
  
  // Check if enough time has passed to move servo7
  if (currentMillis - previousMillis >= servo7Delay) {
    previousMillis = currentMillis;  // Save the last time the servo was moved
    
    // Move servo7 back and forth between min and max positions
    servo7.write(servo7Pos);  // Set the new position
    
    servo7Pos += servo7Increment;  // Increment or decrement position
    
    // Reverse direction at the limits
    if (servo7Pos >= servo7MaxPos || servo7Pos <= servo7MinPos) {
      servo7Increment = -servo7Increment;  // Reverse the direction
    }
  }
}
