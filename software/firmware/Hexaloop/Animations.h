// Interactive state - used when adjusting joint parameters via serial interface
int interactiveKeyFrames[1][NUM_JOINTS] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
unsigned long interactiveDurations[1] = {1000};
ANIMATION interactive {
  "", 0xff, 1, (int *) &interactiveKeyFrames, (unsigned long*)&interactiveDurations
};


// Predefined animations

ANIMATION centerAll {
  "CA",
  CMD_CA,
  1,
  (int *)new int[1][NUM_JOINTS] {
    {0, 0, 0,
     0, 0, 0,
     0, 0, 0,
     0, 0, 0,
     0, 0, 0,
     0, 0, 0}
  },
  new unsigned long[1]{1000}
};

ANIMATION stand {
  "ST",
  CMD_ST,
  1,
  (int *)new int[1][NUM_JOINTS] {
    {-25,0,-35,
     -25,0,-35, 
     0,0,-35, 
     0,0,-35,
     25,0,-35,
     25,0,-35}
  },
  new unsigned long[1]{1000}
};

ANIMATION sit {
  "SI",
  CMD_SI,
  1,
  (int *)new int[1][NUM_JOINTS] {
    {-25,-40,-35,
     -25,-40,-35, 
     0,-40,-35, 
     0,-40,-35,
     25,-40,-35,
     25,-40,-35}
  },
  new unsigned long[1]{1000}
};

ANIMATION wheel {
  "WH",
  CMD_WH,
  1,
  (int *)new int[1][NUM_JOINTS] {
    {0,-65,70,
    0,-65,70, 
    0,-65,70,
    0,-65,70, 
    0,-65,70,
    0,-65,70}
  },
  new unsigned long[1]{1000}
};

// flex each leg in turn
ANIMATION legTest {
  "LG",
  CMD_LG,
  13,
  (int *)new int[13][NUM_JOINTS] {
    {30,30,30,  0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0},
    {-30,-30,-30,  0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0},
    {0,0,0,  30,30,30,  0,0,0,  0,0,0,  0,0,0,  0,0,0},
    {0,0,0,  -30,-30,-30,  0,0,0,  0,0,0,  0,0,0,  0,0,0},
    {0,0,0,  0,0,0,  30,30,30,  0,0,0,  0,0,0,  0,0,0},
    {0,0,0,  0,0,0,  -30,-30,-30,  0,0,0,  0,0,0,  0,0,0},
    {0,0,0,  0,0,0,  0,0,0,  30,30,30,  0,0,0,  0,0,0},
    {0,0,0,  0,0,0,  0,0,0,  -30,-30,-30,  0,0,0,  0,0,0},
    {0,0,0,  0,0,0,  0,0,0,  0,0,0,  30,30,30,  0,0,0},
    {0,0,0,  0,0,0,  0,0,0,  0,0,0,  -30,-30,-30,  0,0,0},
    {0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0,  30,30,30},
    {0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0,  -30,-30,-30},
    {0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0,  0,0,0}
  },
  new unsigned long[13]{1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000}
};


ANIMATION anims[MAX_ANIM_CMD] = { stand, wheel, legTest, centerAll, sit };
