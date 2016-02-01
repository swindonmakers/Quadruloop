#include "AdafruitServoController.h"

void AdafruitServoController::init(uint8_t SDAPin, uint8_t SCLPin) {
	pwm.begin(SDAPin, SCLPin);
	pwm.setPWMFreq(60);  // 60 Hz updates
}

void AdafruitServoController::setServo(uint8_t num, int pos) {
	pwm.setPWM(num, 0, map(pos, 0, 180, _minPulseLen, _maxPulseLen));
}

void AdafruitServoController::updateServos(){
	// Nothing to do
}
