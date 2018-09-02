#ifndef AdafruitServoController_h
#define AdafruitServoController_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ServoController.h>

class AdafruitServoController : public ServoController {

public:
	void init(uint8_t SDAPin, uint8_t SCLPin);
	void setServo(uint8_t num, int pos);
	void updateServos();

private:
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // pwm driver board interface

	uint16_t _minPulseLen = 150;  // 0 degrees, in range 0..4096
	uint16_t _maxPulseLen = 600;  // 180 degrees, in range 0..4096
};

#endif