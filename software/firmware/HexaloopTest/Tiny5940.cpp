/*------------------------------------------------------------------------
 The TLC5940 controller
------------------------------------------------------------------------*/

#include <Arduino.h>

#define SIN_PIN D0
#define SCLK_PIN D1
#define XLAT_PIN D2

#define NUM_TLCS 2
#define TLC_CHANNEL_TYPE    uint8_t

/** The maximum angle of the servo. */
#define SERVO_MAX_ANGLE     180
/** The 1ms pulse width for zero degrees (0 - 4095). */
#define SERVO_MIN_WIDTH     60
/** The 2ms pulse width for 180 degrees (0 - 4095). */
#define SERVO_MAX_WIDTH     255

#define pulse_pin(pin) digitalWrite(pin, HIGH); digitalWrite(pin, LOW);

class Tiny5940 {
uint8_t tlc_GSData[NUM_TLCS * 24];

public:
void init()
{
  pinMode(XLAT_PIN, OUTPUT);
  digitalWrite(XLAT_PIN, HIGH);
  tlc_shift8_init();
}

void set(TLC_CHANNEL_TYPE channel, uint16_t value)
{
    TLC_CHANNEL_TYPE index8 = (NUM_TLCS * 16 - 1) - channel;
    uint8_t *index12p = tlc_GSData + ((((uint16_t)index8) * 3) >> 1);
    if (index8 & 1) { // starts in the middle
                      // first 4 bits intact | 4 top bits of value
        *index12p = (*index12p & 0xF0) | (value >> 8);
                      // 8 lower bits of value
        *(++index12p) = value & 0xFF;
    } else { // starts clean
                      // 8 upper bits of value
        *(index12p++) = value >> 4;
                      // 4 lower bits of value | last 4 bits intact
        *index12p = ((uint8_t)(value << 4)) | (*index12p & 0xF);
    }
}

void setAll(uint16_t value)
{
    uint8_t firstByte = value >> 4;
    uint8_t secondByte = (value << 4) | (value >> 8);
    uint8_t *p = tlc_GSData;
    while (p < tlc_GSData + NUM_TLCS * 24) {
        *p++ = firstByte;
        *p++ = secondByte;
        *p++ = (uint8_t)value;
    }
}
 
void setServo(byte channel, uint8_t angle)
{
    set(channel, angleToVal(angle));
}

void setAllServo(uint8_t angle)
{
  setAll(angleToVal(angle));
}

/* 
 * Clock out the current servo settings and latch 
 * Takes approx 750us
 */

 long lastUpdate = 0;
 #define UPDATE_RATE_LIMIT 25
bool update() 
{
  // Limit update rate of servos or we end up latching in new
  // values before the old values are set
  if (millis() - lastUpdate < UPDATE_RATE_LIMIT)
    return false;

  // Clock out data
  pulse_pin(SCLK_PIN);
  uint8_t *p = tlc_GSData;
  while (p < tlc_GSData + NUM_TLCS * 24) {
    tlc_shift8(*p++);
  }
  pulse_pin(SCLK_PIN);
    
  // Pulse XLAT low to tell Attiny that it should
  // pulse XLAT at the end of the GSCLK cycle
  digitalWrite(XLAT_PIN, LOW);
  delayMicroseconds(10); // small delay because ESP runs quicker than ATTiny
  digitalWrite(XLAT_PIN, HIGH);

  lastUpdate = millis();

  return true;
}


private:
/** Converts and angle (0 - SERVO_MAX_ANGLE) to the inverted tlc channel value
    (4095 - 0). */
uint16_t angleToVal(uint8_t angle)
{
    return 4095 - SERVO_MIN_WIDTH - (
            ((uint16_t)(angle) * (uint16_t)(SERVO_MAX_WIDTH - SERVO_MIN_WIDTH))
            / SERVO_MAX_ANGLE);
}

void tlc_shift8_init(void)
{
  pinMode(SIN_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  digitalWrite(SCLK_PIN, LOW);
}

/** Shifts a byte out, MSB first */
void tlc_shift8(uint8_t byte)
{
    for (uint8_t bit = 0x80; bit; bit >>= 1) {
        if (bit & byte) {
          digitalWrite(SIN_PIN, HIGH);
        } else {
          
          digitalWrite(SIN_PIN, LOW);
        }
        
        pulse_pin(SCLK_PIN);
    }
}
};
