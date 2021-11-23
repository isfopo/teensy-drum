#include <Arduino.h>
#include <hellodrum.h>

#define MIDI_CHANNEL 0

byte KICK[6] = {
    100, //sensitivity (1-100)
    35,  //threshold (1-100)
    10,  //scan time (1-)
    35,  //mask time (1-)
    36,  //note (0-127)
    1    //curve type (0-4)
};

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

HelloDrum kick(12);
HelloDrum snare(10, 11);

void setup() {
  kick.setCurve(KICK[5]);
  snare.setCurve(SNARE[6]);
}

void loop() {
  kick.singlePiezo(KICK[0], KICK[1], KICK[2], KICK[3]);
  snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]);

  if (kick.hit == true) {
    usbMIDI.sendNoteOn(KICK[4], kick.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(KICK[4], 0, MIDI_CHANNEL);
  }

  if (snare.hit == true)
  {
    usbMIDI.sendNoteOn(SNARE[7], snare.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(SNARE[7], 0, MIDI_CHANNEL);
  }
  else if (snare.hitRim == true)
  {
      usbMIDI.sendNoteOn(SNARE[8], snare.velocity, MIDI_CHANNEL); //(note, velocity, channel)
      usbMIDI.sendNoteOff(SNARE[8], 0, MIDI_CHANNEL);
  }
}