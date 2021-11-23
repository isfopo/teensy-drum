#include <Arduino.h>
#include <hellodrum.h>

byte SNARE[9] = {
    90, //sensitivity (1-100)
    50,  //threshold (1-100)
    30,  //scan time (1-100)
    10,  //mask time (1-100)
    10,  //rim sensitivity (1-100)
    3,   //rim threshold (1-100)
    3,   //curve type (0-4)
    38,  //note (0-127)
    37   //note of cross stick (0-127)
};

HelloDrum snare(10, 11);

void setup() {
  snare.setCurve(SNARE[6]);
}

void loop() {
    snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]);

  if (snare.hit == true)
  {
    usbMIDI.sendNoteOn(SNARE[7], snare.velocity, 10); //(note, velocity, channel)
    usbMIDI.sendNoteOff(SNARE[7], 0, 10);
  }
  else if (snare.hitRim == true)
  {
      usbMIDI.sendNoteOn(SNARE[8], snare.velocity, 10); //(note, velocity, channel)
      usbMIDI.sendNoteOff(SNARE[8], 0, 10);
  }
}