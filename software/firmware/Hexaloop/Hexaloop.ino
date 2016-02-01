#include "Config.h"

#include <ServoAnimator.h>
#include <TLC5940ServoController.h>
#include <QuadruloopEEPROM.h>
#include <CommandQueue.h>

#include "Animations.h"

TLC5940ServoController servoController;
ServoAnimator anim(NUM_JOINTS);
CommandQueue cmdQ(COMMAND_QUEUE_LENGTH);

String cmd;  // cmd received over serial - builds up char at a time

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Hexaloop");

  QuadruloopEEPROM::loadConfig(NUM_JOINTS, servoCenters);

  servoController.init(D0, D1, D2);
  anim.begin(servoController);
  
  // init servos
  for (uint8_t i=0; i<NUM_JOINTS; i++)
      anim.initServo(i, servoNumbers[i], servoCenters[i], servoReverse[i]);

  anim.setAnimation(centerAll);
  //anim.setAnimation(legTest);
}

void updateInteractivePositions() {
    anim.setAnimation(interactive);

    // debug
    for (uint8_t i=0; i<NUM_JOINTS; i++) {
        if (i>0) Serial.print(',');
        Serial.print(interactiveKeyFrames[0][i]);
    }
    Serial.println();
}

void doCommand(COMMAND *c)
{
    if (c == NULL) return;

    // Parse out parameter values
    int sp = c->cmd.indexOf(' ');
    float f1 = 0;
    float f2 = 0;
    if (sp > -1) {
        f1 = c->cmd.substring(0,sp).toFloat();
        f2 = c->cmd.substring(sp+1).toFloat();
    } else {
        f1 = c->cmd.toFloat();
    }

    // Handle the animation commands that can be "auto" processed
    if (c->cmdType <= MAX_ANIM_CMD) {
      for (int i = 0; i < sizeof(anims) / sizeof(anims[0]); i++) {
        if (anims[i].cmdType == c->cmdType) {
          anim.setAnimation(anims[i]);
          anim.setRepeatCount(f1);
          return;
        }
      }
    }

    // Handle all the other commands that can't be dealt with by the "auto" process
    switch(c->cmdType) {
        case CMD_POS:
            if (f1 >= 0 && f1 <= NUM_JOINTS-1) {
                interactiveKeyFrames[0][(uint8_t)f1] = (int)f2;
            }
            updateInteractivePositions();
            break;
        case CMD_SV:
            QuadruloopEEPROM::saveConfig(NUM_JOINTS, servoCenters);
            break;
        case CMD_SC:
            if (f1 < 0 || f1 > NUM_JOINTS-1) break;
            if (c->cmd == "") {
              for (int i = 0; i < NUM_JOINTS; i++) {
                Serial.print(servoCenters[i]);
                Serial.print(",");
              }
              Serial.println();
            } else {
              servoCenters[(uint8_t)f1] = (uint8_t)f2;
              anim.setServoCenter((uint8_t)f1, (uint8_t)f2);
              updateInteractivePositions();
              //anim.setAnimation(stand);
            }
            break;
    }
}

void parseCommand(String c) {
    // parse and queue/insert
    uint8_t cmdType = 0xff;

    // check for urgent commands
    boolean doNow = false;
    if (c[0] == '!') {
        doNow = true;
        c = c.substring(1);
    }

    // parse the command type
    for (int i = 0; i < sizeof(anims) / sizeof(anims[0]); i++)
      if (c.startsWith(anims[i].cmd))
        cmdType = anims[i].cmdType;

    if (cmdType != 0xff) {
      // already matches an animation
    } else if (c.startsWith("SV")) {
        cmdType = CMD_SV;
    } else if (c.startsWith("SC")) {
        cmdType = CMD_SC;
    } else if (c.startsWith("POS")) {
        cmdType = CMD_POS;
    }

    // give up if command not recognised
    if (cmdType == 0xff) return;

    // lose the command name, keep the parameters
    int sp = c.indexOf(' ');
    if (sp > -1) {
        c = c.substring(sp+1);
    } else {
        c = "";
    }

    // insert/queue the command
    if (doNow) {
        anim.stop();  // stop the bot
        cmdQ.insert(c, cmdType);  // insert the new command at the head of the command queue
    } else {
        cmdQ.enqueue(c, cmdType);
    }
}

void loop() {
  anim.update();

  // Parse commands from Serial
  if (Serial.available()) {
    char c = toupper(Serial.read());
    if (c == '\r' || c == '\n') {  // if found a line end
      if (cmd != "") {  // check the command isn't blank
        if (cmdQ.isFull()) {
          Serial.println("BUSY");
        } else {
          parseCommand(cmd);
          Serial.println("OK:" + cmd);
        }
        
        // reset the command buffer
        cmd = "";
      }
      
    } else {
      cmd += c;  // append the character onto the command buffer
    }
  }

  if (!anim.isBusy()) {
    if (!cmdQ.isEmpty()) 
      doCommand(cmdQ.dequeue());
  }
}
