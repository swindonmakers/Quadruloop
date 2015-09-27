/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// servo driver on default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// limits
//#define SERVOMIN  150 
//#define SERVOMAX  600 

#define SERVOMIN  150 + 400 / 2 
#define SERVOMAX  150 + 500 / 2

uint16_t servoMins[6] = {300, 250, 250, 250, 350, 250};
uint16_t servoMaxs[6] = {600, 500, 500, 300, 400, 500};


// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Quadruloop servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // 60 Hz updates

  // set start positions
  for (servonum = 0; servonum < 5; servonum++) {
    pwm.setPWM(servonum, 0, servoMins[servonum]);
  }
}

void loop() {
  // Drive each servo one at a time
  Serial.println(servonum);
  for (uint16_t pulselen = servoMins[servonum]; pulselen < servoMaxs[servonum]; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(5);
  }
  delay(250);
  for (uint16_t pulselen = servoMaxs[servonum]; pulselen > servoMins[servonum]; pulselen--) {
    pwm.setPWM(servonum, 0, pulselen);
    delay(5);
  }

  servonum ++;
  if (servonum > 5) servonum = 0;
}
