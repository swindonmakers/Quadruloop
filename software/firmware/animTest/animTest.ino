#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SimpleBezier.h>
#include <ServoAnimatorI2C.h>
#include "Animations.h"

#define NUMSERVOS 6

ServoAnimatorI2C anim(NUMSERVOS);

void setup() {
  anim.begin();

  // init servos
  anim.initServo(0,0,90);
  anim.initServo(1,1,90);
  anim.initServo(2,2,90);
  anim.initServo(3,3,90);
  anim.initServo(4,4,90);
  anim.initServo(5,5,90);

  anim.setAnimation(stand);
}

void loop() {

  anim.update();

  if (!anim.isBusy()) {
      anim.setAnimation(openClose);
  }
}
