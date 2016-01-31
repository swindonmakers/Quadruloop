
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


#define SERVO_CHANNEL_MIN   0
#define SERVO_CHANNEL_MAX   17

const int ANG_MIN = 60;
const int ANG_MAX = 120;


#define pulse_pin(pin) digitalWrite(pin, HIGH); digitalWrite(pin, LOW);


/*------------------------------------------------------------------------
 The TLC5940 controller
------------------------------------------------------------------------*/
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


// Create a Tiny5940 for people to use
Tiny5940 tlc;

long ma;
long mb;

void setup() {
  Serial.begin(115200);
  Serial.println("espTLC5940Hybrid");
  
  // put your setup code here, to run once:
  Serial.println("init");
  tlc.init();
  centerAll();
  delay(2000);

}



void loop()
{
  individualWiggle(10);
  individualWiggle(0);
  centerAll();
  delay(1000);
  
  for (int i = 5; i > 0; i--)
    coordinatedWiggle(2 * i);
  coordinatedWiggle(2);
  coordinatedWiggle(2);
  coordinatedWiggle(2);
  centerAll();
  delay(1000);
  
  for (int i = 0; i < 5; i++)
    fastAs();
  centerAll();
  delay(1000);
}

void centerAll()
{
  Serial.println("Center all");
  for (int c = SERVO_CHANNEL_MIN; c <= 17; c++)
    tlc.setServo(c, 90);
  tlc.update(); 
}

void fastAs()
{
  const int DELAY = 500;
  
  for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
    tlc.setServo(c, ANG_MIN);
  tlc.update();
  delay(DELAY);
  
  //for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
  //  tlc_setServo(c, 90);
  //Tlc.update();
  //delay(DELAY);

  for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
    tlc.setServo(c, ANG_MAX);
  tlc.update();
  delay(DELAY);

  //for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
  //  tlc_setServo(c, 90);
  //Tlc.update();
  //delay(DELAY);
  
}

void coordinatedWiggle(int DELAY_TIME)
{
  const int STEP = 1;
//  const int DELAY_TIME = 10;
  
  for (int angle = 90; angle <= ANG_MAX; angle += STEP) {
    for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
      tlc.setServo(c, angle);
    }
    //if (angle % 10 == 0)
      //Serial.println(angle);
    
    tlc.update();
    delay(DELAY_TIME);
  }
  for (int angle = ANG_MAX; angle >= ANG_MIN; angle -= STEP) {
    for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
      tlc.setServo(c, angle);
    }
    //if (angle % 10 == 0)
      ///Serial.println(angle);
    
    tlc.update();
    delay(DELAY_TIME);
  }
  for (int angle = ANG_MIN; angle <= 90; angle += STEP) {
    for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
      tlc.setServo(c, angle);
    }
    //if (angle % 10 == 0)
      //Serial.println(angle);
    
    tlc.update();
    delay(DELAY_TIME);
  }
}

void individualWiggle(int DELAY_TIME)
{
  //const int DELAY_TIME = 3;
  
  for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
    //Serial.print("*** Channel:");
    //Serial.println(c);
    
    for (int angle = 90; angle <= ANG_MAX; angle++) {
      //if (angle % 10 == 0)
        //Serial.println(angle);
      tlc.setServo(c, angle);
      tlc.update();
      delay(DELAY_TIME);
    }

    for (int angle = ANG_MAX; angle >= ANG_MIN; angle--) {
      //if (angle % 10 == 0) 
        //Serial.println(angle);
      tlc.setServo(c, angle);
      tlc.update();
      delay(DELAY_TIME);
    }

    for (int angle = ANG_MIN; angle <= 90; angle++) {
      //if (angle % 10 == 0)
        //Serial.println(angle);
      tlc.setServo(c, angle);
      tlc.update();
      delay(DELAY_TIME);
    }
  }  
}

int pos = 90;
int dir = 1;

void testloop() {
  pos += dir;
  tlc.setServo(0, pos);
  tlc.setServo(1, 180-pos);
  //tlc.setAllServo(pos);
  ma = micros();
  tlc.update();
  mb = micros();
  Serial.print(pos);
  Serial.print(" : ");
  Serial.println(mb - ma);

  if (pos == 180 || pos == 0) dir *= -1;

  if (pos % 90 == 0) {
    while (!tlc.update()) {} 
    delay(2000);
  }  else {
    delay(5);
  }
}
