#define NUM_JOINTS 18

#define COMMAND_QUEUE_LENGTH 8

/*
Servo wiring - Back is at the usb port of the NodeMCU

0 - back left hip
1 - back left coxa
2 - back left tibia

3 - back right hip
4 - back right coxa
5 - back right tibia

6 - mid left hip
7 - mid left coxa
8 - mid left tibia

9 - mid right hip
10 - mid right coxa
11 - mid right tibia

12 - front left hip
13 - front left coxa
14 - front left tibia

15 - front right hip
16 - front right coxa
17 - front right tibia


*/
uint8_t servoNumbers[NUM_JOINTS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

// default centers - will be overwritten from EEPROM once calibrated
uint8_t servoCenters[NUM_JOINTS] = {90,90,90, 90,90,90, 90,90,90, 90,90,90, 90,90,90, 90,90,90};
// RL calibration: 96,93,100,96,82,83,75,85,88,83,90,90,107,88,70,90,115,97,

// Positive joint directions should be:
// Hip - turns towards front
// Coxa - turns towards the ground
// Femur - turns towards the ground
boolean servoReverse[NUM_JOINTS] = {
  true, false, true, 
  false, true, false, 
  true, false, true, 
  false, true, false,
  true, true, false, 
  false, false, true
};

// Commands

// command values
#define CMD_ST 0
#define CMD_WH 1
#define CMD_LG 2
#define CMD_CA 3
#define CMD_SI 4
#define CMD_FD 5
#define CMD_FE 6
#define CMD_RR 7

#define MAX_ANIM_CMD CMD_RR+1 // First command that isn't tied to an animation

#define CMD_PRE 20 // set position of servo x to y (relative to center) but dont move to it yet
#define CMD_POS 21 // set position of servo x to y (relative to center)
#define CMD_IA 22 // make the current stance the interactive stance.  So (eg) send ST, IA, then use POS commands to tweak the ST)
#define CMD_SV 23  // save config
#define CMD_SC 24 // servo center - set servo x center to y (abs)
#define CMD_PF 25 // pause for x seconds
#define CMD_CP 26 // copy current position into interactive animation keyframe
#define CMD_BK 27 // Back (reverse FD)


// Modes
#define MODE_INTERACTIVE 0
#define MODE_TEST 1  // loop through test movements


#define WIFI_SSID "HEXALOOP"
#define WIFI_PASS "HEXALOOP"