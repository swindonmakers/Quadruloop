#include "ServoAnimatorI2C.h"

ServoAnimatorI2C::ServoAnimatorI2C(uint8_t numServos) {
    _numServos = numServos;
    _servos = new SERVO[_numServos];
}

void ServoAnimatorI2C::begin() {
    pwm.begin();
    pwm.setPWMFreq(60);  // 60 Hz updates
}

void ServoAnimatorI2C::initServo(uint8_t num, uint8_t pin, uint8_t center) {
    if (num >= _numServos) return;
    SERVO *s = &_servos[num];

    s->pin = pin;
    s->center = center;
    s->pos = center;
    s->targetPos = center;
    s->startPos = center;

    // center servo
    pwm.setPWM(s->pin, 0, map(s->pos, 0, 180, _minPulseLen, _maxPulseLen));
}

void ServoAnimatorI2C::setServoCenter(uint8_t num, uint8_t center) {
    if (num >= _numServos) return;
    SERVO *s = &_servos[num];
    s->center = center;
}

void ServoAnimatorI2C::moveServosTo(const byte keyframe[], unsigned long dur) {
   if (_busy) return;

   _moveStartedAt = millis();
   _busy = true;
   _moveDuration = dur * (1.0/_speed);
   for (uint8_t i=0; i<_numServos; i++) {
       _servos[i].targetPos = _servos[i].center + keyframe[i];

       /*
       Serial.print(i);
       Serial.print(':');
       Serial.print(keyframe[i]);
       Serial.print(',');
       Serial.println(_servos[i].targetPos);
       */
   }

}

void ServoAnimatorI2C::setAnimation(ANIMATION& animation, boolean reverse) {
    _animation = &animation;
    _reverse = reverse;
    setRepeatCount(0);
    moveToFrame(_reverse ? _animation->numFrames-1 : 0);
}

void ServoAnimatorI2C::setRepeatCount(uint8_t repeatCount) {
    _repeatCount = repeatCount;
}

void ServoAnimatorI2C::setSpeed(float speed) {
    if (speed <= 0) return;
    _speed = speed;
}

boolean ServoAnimatorI2C::isBusy() {
    return _busy;
}

void ServoAnimatorI2C::update() {
  if (!_busy || _moveDuration == 0) return; // nothing to do

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
    pwm.setPWM(_servos[i].pin, 0, map(_servos[i].pos, 0, 180, _minPulseLen, _maxPulseLen));
  }

  // see if we're done with the current move
  if (t>=1) {
    _busy = false;
    for (uint8_t i=0; i<_numServos; i++)
      _servos[i].startPos = _servos[i].pos;

    // play next keyFrame?
    nextFrame();
  }
}

boolean ServoAnimatorI2C::moveToFrame(uint8_t frame) {
    if (_animation ==0 || frame >= _animation->numFrames) return false;
    _animFrame = frame;
    /*
    Serial.print('F');
    Serial.println(_animFrame);
    */
    moveServosTo(&_animation->frames[_animFrame * _numServos], _animation->durations[_animFrame]);
    return true;
}

void ServoAnimatorI2C::nextFrame() {
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

void ServoAnimatorI2C::stop() {
    _busy = false;
    for (uint8_t i=0; i<_numServos; i++)
      _servos[i].startPos = _servos[i].pos;
}
