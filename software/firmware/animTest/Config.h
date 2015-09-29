#define NUM_JOINTS 12

#define COMMAND_QUEUE_LENGTH 8

/*
Servo wiring

0 - front left hip
1 - front left coxa
2 - front left tibia

3 - back left hip
4 - back left coxa
5 - back left tibia

6 - front right hip
7 - front right coxa
8 - front right tibia

9 - back right hip
10 - back right coxa
11 - back right tibia

*/


// default centers - will be overwritten from EEPROM once calibrated
uint8_t servoCenters[NUM_JOINTS] = {90,90,90, 90,90,90, 90,90,90, 90,90,90};


boolean servoReverse[NUM_JOINTS] = {
  false, false, true, 
  true, true, false, 
  true, true, false, 
  false, false, true
};

// Commands

// command values
#define CMD_ST 0
#define CMD_WH 1

#define MAX_ANIM_CMD 2 // First command that isn't tied to an animation

#define CMD_POS 21 // set position of servo x to y (relative to center)

#define CMD_SV 23  // save config
#define CMD_SC 24 // servo center - set servo x center to y (abs)
#define CMD_PF 25 // pause for x seconds


// Modes
#define MODE_INTERACTIVE 0
#define MODE_TEST 1  // loop through test movements
