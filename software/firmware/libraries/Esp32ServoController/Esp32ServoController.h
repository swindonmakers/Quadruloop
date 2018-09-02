#ifndef Esp32ServoController_H
#define Esp32ServoController_H

#include <Arduino.h>
#include <ServoController.h>

#define MCPWM_DUTY_MIN 550
#define MCPWM_DUTY_MAX 2800
#define MCPWM_DUTY_MID MCPWM_DUTY_MIN + (MCPWM_DUTY_MAX - MCPWM_DUTY_MIN) / 2

#define MAX_INT 65535

// Note, we can't really change either of these two .._N_SERVOS values
// without updating code elsewhere as well
#define LEDC_N_SERVOS 15
#define MCPWM_N_SERVOS 3

class Esp32ServoController : public ServoController {

public:
    void init();
    void setServo(uint8_t num, int pos);
    void updateServos();

private:

    uint32_t servoMax = MAX_INT / 20000 * MCPWM_DUTY_MAX; 
    uint32_t servoMin = MAX_INT / 20000 * MCPWM_DUTY_MIN;
    uint32_t servoMid = servoMin + (servoMax - servoMin) / 2;
    
    // LEDC has 16 channels max, we use 15
    byte ledcServoPins[LEDC_N_SERVOS] = {15,2,4,  16,17,5,  18,19,21,  13,12,14,   27,26,25 };
    // MCPWM has ? channels max, we use 3
    byte mcpwmServoPins[MCPWM_N_SERVOS] = {33,22,23};

};

#endif