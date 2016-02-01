#include "Config.h"

#include <ServoAnimator.h>
#include <TLC5940ServoController.h>
#include <QuadruloopEEPROM.h>

#include "Animations.h"


TLC5940ServoController servoController;
ServoAnimator anim(NUM_JOINTS);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Hexaloop");

  QuadruloopEEPROM::loadConfig(NUM_JOINTS, servoCenters);

  servoController.init(D0, D1, D2);
  anim.begin(servoController);
  
  // init servos
  for (uint8_t i=0; i<NUM_JOINTS; i++)
      anim.initServo(i, servoNumbers[i], servoCenters[i], servoReverse[i]);

  //anim.setAnimation(centerAll);
  anim.setAnimation(legTest);
}

void loop() {
  anim.update();
}
