#define NUM_JOINTS 6

#define COMMAND_QUEUE_LENGTH 8

// default centers - will be overwritten from EEPROM once calibrated
uint8_t servoCenters[NUM_JOINTS] = {90,90,90,90,90,90};


// Commands

// command values
#define CMD_ST 0
#define CMD_OC 1

#define MAX_ANIM_CMD 2 // First command that isn't tied to an animation

#define CMD_POS 21 // set position of servo x to y (relative to center)

#define CMD_SV 23  // save config
#define CMD_SC 24 // servo center - set servo x center to y (abs)
