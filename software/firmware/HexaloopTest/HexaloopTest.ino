#include "Tiny5940.cpp"

#define SERVO_CHANNEL_MIN   0
#define SERVO_CHANNEL_MAX   17

const int ANG_MIN = 60;
const int ANG_MAX = 120;

Tiny5940 tlc;

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

  for (int c = SERVO_CHANNEL_MIN; c <= SERVO_CHANNEL_MAX; c++)
    tlc.setServo(c, ANG_MAX);
  tlc.update();
  delay(DELAY);
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

