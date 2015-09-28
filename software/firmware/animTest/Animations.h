#define NUM_JOINTS 6

// command values
#define CMD_ST 0
#define CMD_OC 1

ANIMATION stand {
  "ST",
  CMD_ST,
  1,
  (byte *)new byte[1][NUM_JOINTS] {
    {0,0,0,0,0,0}
  },
  new unsigned long[1]{500}
};

ANIMATION openClose {
  "OC",
  CMD_OC,
  2,
  (byte *)new byte[2][NUM_JOINTS] {
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
  },
  new unsigned long[2]{1000,1000}
};
