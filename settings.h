#include "Arduino.h"

/*
/////////////////////////////////////////////////////////////////////////
// KEY MAPPINGS: WHICH KEY MAPS TO WHICH PIN ON THE MAKEY MAKEY BOARD? //
/////////////////////////////////////////////////////////////////////////

  - edit the midiInputs array below to change the keys sent by the MaKey MaKey for each input
  - the comments tell you which input sends that key (for example, by default 'w' is sent by pin D5)
  - change the keys by replacing them. for example, you can replace 'w' with any other individual letter,
    number, or symbol on your keyboard
  - you can also use codes for other keys such as modifier and function keys (see the
    the list of additional key codes at the bottom of this file)
*/


//////////////////////////////
// MIDI NOTE CODES
//////////////////////////////
#define LOW_NOTE    0x2E // E2
#define LOW_CONTROL 60


struct MidiCode {
  int code;
  boolean control;
  boolean onState;
};


MidiCode midiInputs[NUM_INPUTS] = {

  // top side of the makey makey board

  { LOW_CONTROL,     true, false },    // up arrow pad
  { LOW_CONTROL + 1, true, false },    // down arrow pad
  { LOW_NOTE + 6,    false, false },   // left arrow pad   (PALM/WRIST HIT)
  { LOW_CONTROL + 3, true, false },    // right arrow pad
  { LOW_CONTROL + 4, true, false },    // space button pad
  { LOW_CONTROL + 2, true, false },    // click button pad


  // female header on the back left side

  { LOW_NOTE,     false, false },      // pin D5
  { LOW_NOTE + 1, false, false },      // pin D4
  { LOW_NOTE + 2, false, false },      // pin D3
  { LOW_NOTE + 3, false, false },      // pin D2
  { LOW_NOTE + 4, false, false },      // pin D1
  { LOW_NOTE + 5, false, false },      // pin D0


  // female header on the back right side

  { LOW_CONTROL + 5, true, false },    // pin A5
  { LOW_CONTROL + 6, true, false },    // pin A4
  { LOW_CONTROL + 7, true, false },    // pin A3
  { LOW_CONTROL + 8, true, false },    // pin A2
  { LOW_CONTROL + 9, true, false },    // pin A1
  { LOW_CONTROL + 10, true, false }    // pin A0
};


///////////////////////////
// NOISE CANCELLATION /////
///////////////////////////
#define SWITCH_THRESHOLD_OFFSET_PERC  5    // number between 1 and 49
                                           // larger value protects better against noise oscillations, but makes it harder to press and release
                                           // recommended values are between 2 and 20
                                           // default value is 5

#define SWITCH_THRESHOLD_CENTER_BIAS 55   // number between 1 and 99
                                          // larger value makes it easier to "release" keys, but harder to "press"
                                          // smaller value makes it easier to "press" keys, but harder to "release"
                                          // recommended values are between 30 and 70
                                          // 50 is "middle" 2.5 volt center
                                          // default value is 55
                                          // 100 = 5V (never use this high)
                                          // 0 = 0 V (never use this low
