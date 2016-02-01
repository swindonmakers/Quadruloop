#ifndef ServoAnimator_h
#define ServoAnimator_h

#include <stdlib.h>
#include <Arduino.h>

#include <SimpleBezier.h>
#include <ServoController.h>

struct ANIMATION {
    char cmd[3];
    uint8_t cmdType;
    uint8_t numFrames;
    int *frames;
    unsigned long *durations;
};


class ServoAnimator {
private:
    struct SERVO {
        uint8_t pin;
        int center;
        boolean reverse;
        int startPos;
        int targetPos;
        int pos;
    };

    uint8_t _numServos;
    SERVO *_servos; // array of servo structures
	ServoController * _servoController;

    // how long to take in ms to get to targetPos from startPos
    unsigned long _moveDuration = 250;

    // millis() value at the start of the move
    unsigned long _moveStartedAt = 0;

    // move status flag - true when moving, cleared by update()
    boolean _busy = false;

    ANIMATION * _animation;

    uint8_t _animFrame = 0;
    uint8_t _repeatCount = 0;
    boolean _reverse = false; // set to true to reverse animation
    float _speed = 1.0;  // multiplier applied to animation timings
    unsigned long _updateCount = 0;

public:

    ServoAnimator (uint8_t numServos);
    void begin(ServoController& servoController);
    void initServo(uint8_t num, uint8_t pin, uint8_t center, boolean reverse = false);
    void setServoCenter(uint8_t num, uint8_t center);
    int getServoPos(uint8_t num, boolean relative);

    void moveServosTo(const int keyframe[], unsigned long dur);
    void setAnimation(ANIMATION& animation, boolean reverse = false);
    void setRepeatCount(uint8_t repeatCount);
    void setSpeed(float speed);

    boolean isBusy();

    void update();
    boolean moveToFrame(uint8_t frame); // returns false when done
    void nextFrame();

    void stop();

};

#endif
