// Interactive state - used when adjusting joint parameters via serial interface
int interactiveKeyFrames[1][NUM_JOINTS] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
unsigned long interactiveDurations[1] = {1000};
ANIMATION interactive {
  "", 0xff, 1, (int *) &interactiveKeyFrames, (unsigned long*)&interactiveDurations
};


// Predefined animations

ANIMATION stand {
  "ST",
  CMD_ST,
  1,
  (int *)new int[1][NUM_JOINTS] {
    {0,85,-20,
     0,85,-20, 
     0,85,-20,
     0,85,-20}
  },
  new unsigned long[1]{1000}
};

ANIMATION wheel {
  "WH",
  CMD_WH,
  1,
  (int *)new int[1][NUM_JOINTS] {
    {0,-32,120,0,-38,120, 0,-32,120,0,-38,120}
  },
  new unsigned long[1]{1000}
};

// flex each leg in turn
ANIMATION legTest {
  "LG",
  CMD_LG,
  5,
  (int *)new int[5][NUM_JOINTS] {
    {10,10,10,  0,0,0,  0,0,0,  0,0,0},
    {0,0,0,  10,10,10,  0,0,0,  0,0,0},
    {0,0,0,  0,0,0,  10,10,10,  0,0,0},
    {0,0,0,  0,0,0,  0,0,0,  10,10,10},
    {0,0,0,  0,0,0,  0,0,0,  0,0,0}
  },
  new unsigned long[5]{1000,1000,1000,1000,1000}
};


ANIMATION anims[MAX_ANIM_CMD] = { stand, wheel, legTest };
