#include "Esp32ServoController.h"
#include "driver/mcpwm.h"

void Esp32ServoController::init() {
    // Setup ledc servos
    for (byte i = 0; i < LEDC_N_SERVOS; i++) {
        byte channel = i;
        byte servoPin = ledcServoPins[i];

        ledcSetup(channel, 50, 16); // channel X, 50 Hz, 16-bit depth
        ledcAttachPin(servoPin, channel);   // GPIO servoPin on channel X
        ledcWrite(channel, servoMid); // Set initial (midpoint) position
    }

    // Setup MCPWM servos
    // Setup which MCPWM units are linked to which pins
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, mcpwmServoPins[0]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, mcpwmServoPins[1]);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, mcpwmServoPins[2]);

    // Configure MCPWM parameters
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwm_config.cmpr_a = MCPWM_DUTY_MID;    //duty cycle of PWMxA
    pwm_config.cmpr_b = MCPWM_DUTY_MID;    //duty cycle of PWMxb
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);    //Configure PWM1A & PWM1B with same settings

    // Set some initial positions
    // TODO: surely this shouldn't be required?
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MID);
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MID);
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MID);
}

void Esp32ServoController::setServo(uint8_t num, int pos){

    if (num < LEDC_N_SERVOS) {
        ledcWrite(num, map(pos, 0, 180, servoMin, servoMax));
    }

    else {
        switch (num) {
            case 15:
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, map(pos, 0, 180, MCPWM_DUTY_MIN, MCPWM_DUTY_MAX));
                break;
            case 16:
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, map(pos, 0, 180, MCPWM_DUTY_MIN, MCPWM_DUTY_MAX));
                break;
            case 17:
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, map(pos, 0, 180, MCPWM_DUTY_MIN, MCPWM_DUTY_MAX));
                break;
        }
    }
}

void Esp32ServoController::updateServos() {
    // Nothing to do
}