/* 
 * Tests the basic function of the Hexaloop using the ESP32 servo driver. 
 * Tests get more and more aggressive on power.
 * Use "ESP32 Dev Module"
 */

#include <ServoController.h>
#include <Esp32ServoController.h>

#define SERVO_CHANNEL_MIN   0
#define SERVO_CHANNEL_MAX   17

const int ANG_MIN = 60;
const int ANG_MAX = 120;

Esp32ServoController svo;

void setup() {
  Serial.begin(115200);
  Serial.println("Esp32 ServoController Test");
  
  Serial.println("init");
  svo.init();
  centerAll();
  delay(2000);
}

void loop()
{
  Serial.println("Wiggle1");
  individualWiggle(10);
  Serial.println("Wiggle2");
  individualWiggle(0);
  Serial.println("CenterAll");
  centerAll();
  delay(1000);
  
  Serial.println("Coordinated Wiggle");
  for (int i = 5; i > 0; i--)
    coordinatedWiggle(2 * i);
  coordinatedWiggle(2);
  coordinatedWiggle(2);
  coordinatedWiggle(2);
  centerAll();
  delay(1000);
  
  Serial.println("FastAs");
  for (int i = 0; i < 5; i++)
    fastAs();
  centerAll();
  delay(1000);
}

void centerAll()
{
  Serial.println("Center all");
  for (int c = SERVO_CHANNEL_MIN; c <= 17; c++)
    svo.setServo(c, 90);
  svo.updateServos(); 
}

void fastAs()
{
  const int DELAY = 500;
  
  for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
    svo.setServo(c, ANG_MIN);
  svo.updateServos();
  delay(DELAY);

  for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
    svo.setServo(c, ANG_MAX);
  svo.updateServos();
  delay(DELAY);
}

void coordinatedWiggle(int DELAY_TIME)
{
  const int STEP = 1;
//  const int DELAY_TIME = 10;
  
  for (int angle = 90; angle <= ANG_MAX; angle += STEP) {
    for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
      svo.setServo(c, angle);
    }
    //if (angle % 10 == 0)
      //Serial.println(angle);
    
    svo.updateServos();
    delay(DELAY_TIME);
  }
  for (int angle = ANG_MAX; angle >= ANG_MIN; angle -= STEP) {
    for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
      svo.setServo(c, angle);
    }
    //if (angle % 10 == 0)
      ///Serial.println(angle);
    
    svo.updateServos();
    delay(DELAY_TIME);
  }
  for (int angle = ANG_MIN; angle <= 90; angle += STEP) {
    for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++) {
      svo.setServo(c, angle);
    }
    //if (angle % 10 == 0)
      //Serial.println(angle);
    
    svo.updateServos();
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
      svo.setServo(c, angle);
      svo.updateServos();
      delay(DELAY_TIME);
    }

    for (int angle = ANG_MAX; angle >= ANG_MIN; angle--) {
      //if (angle % 10 == 0) 
        //Serial.println(angle);
      svo.setServo(c, angle);
      svo.updateServos();
      delay(DELAY_TIME);
    }

    for (int angle = ANG_MIN; angle <= 90; angle++) {
      //if (angle % 10 == 0)
        //Serial.println(angle);
      svo.setServo(c, angle);
      svo.updateServos();
      delay(DELAY_TIME);
    }
  }  
}

