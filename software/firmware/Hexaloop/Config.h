#define NUM_JOINTS 18

#define COMMAND_QUEUE_LENGTH 8

/*
Servo wiring - TODO fix this

0 - front left hip
1 - front left coxa
2 - front left tibia

4 - back left hip
5 - back left coxa
6 - back left tibia

8 - front right hip
9 - front right coxa
10 - front right tibia

12 - back right hip
13 - back right coxa
14 - back right tibia

*/
uint8_t servoNumbers[NUM_JOINTS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

// default centers - will be overwritten from EEPROM once calibrated
uint8_t servoCenters[NUM_JOINTS] = {90,90,90, 90,90,90, 90,90,90, 90,90,90, 90,90,90, 90,90,90};

// Positive joint directions should be:
// Hip - turns towards side of body
// Coxa - turns towards the ground
// Femur - turns towards the ground
boolean servoReverse[NUM_JOINTS] = {
  true, true, false, 
  false, false, true, 
  true, true, false, 
  false, false, true
};

// Commands

// command values
#define CMD_ST 0
#define CMD_WH 1
#define CMD_LG 2
#define CMD_CA 3

#define MAX_ANIM_CMD CMD_LG+1 // First command that isn't tied to an animation

#define CMD_POS 21 // set position of servo x to y (relative to center)

#define CMD_SV 23  // save config
#define CMD_SC 24 // servo center - set servo x center to y (abs)
#define CMD_PF 25 // pause for x seconds
#define CMD_CP 26 // copy current position into interactive animation keyframe


// Modes
#define MODE_INTERACTIVE 0
#define MODE_TEST 1  // loop through test movements
