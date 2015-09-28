// Interactive state - used when adjusting joint parameters via serial interface
byte interactiveKeyFrames[1][NUM_JOINTS] = {
  {0, 0, 0, 0, 0, 0}
};
unsigned long interactiveDurations[1] = {1000};
ANIMATION interactive {
  "", 0xff, 1, (byte *) &interactiveKeyFrames, (unsigned long*)&interactiveDurations
};


// Predefined animations

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
    {10,10,10,10,10,10}
  },
  new unsigned long[2]{1000,1000}
};


ANIMATION anims[MAX_ANIM_CMD] = { stand, openClose };
