#include "ServoAnimator.h"

ServoAnimator::ServoAnimator(uint8_t numServos) {
    _numServos = numServos;
    _servos = new SERVO[_numServos];
}

void ServoAnimator::begin(ServoController& servoController) {
	_servoController = &servoController;
}

void ServoAnimator::initServo(uint8_t num, uint8_t pin, uint8_t center, boolean reverse) {
    if (num >= _numServos) return;
    SERVO *s = &_servos[num];

    s->pin = pin;
    s->center = center;
    s->reverse = reverse;
    s->pos = center;
    s->targetPos = center;
    s->startPos = center;

    // center servo
	_servoController->setServo(s->pin, s->pos);
	_servoController->updateServos();
}

void ServoAnimator::setServoCenter(uint8_t num, uint8_t center) {
    if (num >= _numServos) return;
    SERVO *s = &_servos[num];
    s->center = center;
}

int ServoAnimator::getServoPos(uint8_t num, boolean relative) {
    if (num >= _numServos) return 0;
    if (relative)
        return (_servos[num].pos - _servos[num].center) * (_servos[num].reverse ? -1 : 1);
    else
        return _servos[num].pos;
}

void ServoAnimator::moveServosTo(const int keyframe[], unsigned long dur) {
   if (_busy) return;

   _moveStartedAt = millis();
   _busy = true;
   _moveDuration = dur * (1.0/_speed);
   _updateCount = 0;
   for (uint8_t i=0; i<_numServos; i++) {
       _servos[i].targetPos = (int)_servos[i].center + (_servos[i].reverse ? -keyframe[i] : keyframe[i]);

       /*
       Serial.print(i);
       Serial.print(':');
       Serial.print(keyframe[i]);
       Serial.print(',');
       Serial.println(_servos[i].targetPos);
       */
   }

}

void ServoAnimator::setAnimation(ANIMATION& animation, boolean reverse) {
    _animation = &animation;
    _reverse = reverse;
    setRepeatCount(0);
    moveToFrame(_reverse ? _animation->numFrames-1 : 0);
}

void ServoAnimator::setRepeatCount(uint8_t repeatCount) {
    _repeatCount = repeatCount;
}

void ServoAnimator::setSpeed(float speed) {
    if (speed <= 0) return;
    _speed = speed;
}

boolean ServoAnimator::isBusy() {
    return _busy;
}

void ServoAnimator::update() {
  if (!_busy || _moveDuration == 0) return; // nothing to do

  _updateCount++;

  // calc elapsed time
  float t = millis() - _moveStartedAt;
  if (t < 0) // overflow
    t += 4294967295 - _moveStartedAt;

  t = t / _moveDuration;  // t now in range 0..1
  if (t>=1) t = 1;

  // apply easing - smooth in/out
  t = bezierAt(t, 0, 0.2, 0.8, 1);
  if (t>1) t = 1;
  if (t<0) t = 0;

  for (uint8_t i=0; i<_numServos; i++) {
    // update joint positions
    _servos[i].pos = _servos[i].startPos + t*(_servos[i].targetPos - _servos[i].startPos);

    // update servos
	_servoController->setServo(_servos[i].pin, _servos[i].pos);
  }
  _servoController->updateServos();

  // see if we're done with the current move
  if (t>=1) {
    _busy = false;
    for (uint8_t i=0; i<_numServos; i++)
      _servos[i].startPos = _servos[i].pos;

    Serial.print("Frame ");
    Serial.print(_animFrame);
    Serial.println(" Done");
    /*
    Serial.print("Updates: ");
    Serial.println(_updateCount);
    */

    // play next keyFrame?
    nextFrame();
  }
}

boolean ServoAnimator::moveToFrame(uint8_t frame) {
    if (_animation ==0 || frame >= _animation->numFrames) return false;
    _animFrame = frame;
    /*
    Serial.print('F');
    Serial.println(_animFrame);
    */
    moveServosTo(&_animation->frames[_animFrame * _numServos], _animation->durations[_animFrame]);
    return true;
}

void ServoAnimator::nextFrame() {
    if (_animation ==0) return;
    if (_reverse) {
        _animFrame--;
    } else
        _animFrame++;
    if (!moveToFrame(_animFrame)) {
        if (_repeatCount>1) {
            // restart
            _repeatCount--;
            moveToFrame(_reverse ? _animation->numFrames-1 : 0);
        }
    }
}

void ServoAnimator::stop() {
    _busy = false;
    for (uint8_t i=0; i<_numServos; i++)
      _servos[i].startPos = _servos[i].pos;
}
