#include "InsightMaze.h"
#include "globals.h"

SyringePump r0(SYRINGE_0_STEP_PIN, SYRINGE_0_DIR_PIN, SYRINGE_SPML, SYRINGE_MAX_VOL);
SyringePump r1(SYRINGE_1_STEP_PIN, SYRINGE_1_DIR_PIN, SYRINGE_SPML, SYRINGE_MAX_VOL);
SyringePump r2(SYRINGE_2_STEP_PIN, SYRINGE_2_DIR_PIN, SYRINGE_SPML, SYRINGE_MAX_VOL);
Sensor s0(PIN_SENSOR_0);
Sensor s1(PIN_SENSOR_1);
Sensor s2(PIN_SENSOR_2);
Sensor s3(PIN_SENSOR_3);
Door d0(PIN_DOOR_0, POS_D0[0], POS_D0[1]);
Door d1(PIN_DOOR_1, POS_D1[0], POS_D1[1]);
Door d2(PIN_DOOR_2, POS_D2[0], POS_D2[1]);
Door d3(PIN_DOOR_3, POS_D3[0], POS_D3[1]);
Door d4(PIN_DOOR_4, POS_D4[0], POS_D4[1]);
Door d5(PIN_DOOR_5, POS_D5[0], POS_D5[1]);

Module m(PIN_ID, s0, s1, s2, s3, d0, d1, d2, d3, d4, d5);
EndModule e(PIN_ID, s0, s1, s2, d0, d1, d2, d3, d4, d5, r0, r1, r2);

bool needsToSetPath = false;

int pinsLEDs[] = {13, 12, 8, 7, 4, 2};

void setup() {

  m.moduleSetup();

  for (int i = 0; i < sizeof(pinsLEDs) / sizeof(pinsLEDs[0]); i++) {
    pinMode(pinsLEDs[i], OUTPUT);
    digitalWrite(pinsLEDs[i], LOW);
  }

}

void loop() {

  ////////////// ROCKELLE'S CODE ///////////////////
  // Code for Start Module
  // set path to right
  // close doors on sensor trigger

  // Code for a Module




  ///////////////////////////////////////////////////

  ////////////// JASMINE'S CODE ////////////////////




  //////////////////////////////////////////////////

  ////////////////////GREG's CODE/////////////////////


  ///////////// COMMUNICATION TESTING /////////////

  slavePracticeProtocol();


}

/////////////////////// SYRINGE PUMP CODE //////////////////////////

void testSyringePump(SyringePump syringePump, float mL, int timeDelay) {
  syringePump.dispenseMilliliters(mL);
  delay(timeDelay);
}

void moveSyringePump(SyringePump syringePump, bool isDirUp) {
  if (isDirUp) syringePump.dirUp();
  else syringePump.dirDown();

  syringePump.stepMotor();
}
/////////////////// COMMUNICATION CODE ///////////////////////////////////////////////////////

void doorsAsLEDs(int leds[]) {
  for (int i = 0; i < NUM_MAIN_DOORS; i++) {
    if (m.isDoorOpen(i)) digitalWrite(leds[i], HIGH);
    else digitalWrite(leds[i], LOW);
  }
}

void slavePracticeProtocol() {
  unsigned int commands = m.receiveCommands();

  if (commands != 0) {
    Serial.print(m.id()); Serial.print(" ");
    Serial.print(commands); Serial.print(" ");
    Serial.print(commands, BIN);

    if ((commands & 0b11000000) == 0b10000000) {
      int dir = (commands & 0b00000011);

      switch (dir) {
        case LEFT:
          m.setPath('l');
          break;
        case CENTER:
          m.setPath('c');
          break;
        case RIGHT:
          m.setPath('r');
          break;
      }

      
    }
    Serial.println(' ');
  }

  doorsAsLEDs(pinsLEDs);
}
