#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SimpleBezier.h>
#include <ServoAnimatorI2C.h>

#define NUMSERVOS 6

ServoAnimatorI2C anim(NUMSERVOS);

void setup() {
  // init servos
  anim.initServo(0,0,90);
  anim.initServo(1,1,90);
  anim.initServo(2,2,90);
  anim.initServo(3,3,90);
  anim.initServo(4,4,90);
  anim.initServo(5,5,90);
}

void loop() {
  
}
