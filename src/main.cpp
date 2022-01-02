#include <Arduino.h>
#include <hellodrum.h>

#define MIDI_CHANNEL 0

byte KICK[6] = {
    100, //sensitivity (1-100)
    10,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    36,  //note (0-127)
    3    //curve type (0-4)
};

byte SNARE[9] = {
    90, //sensitivity (1-100)
    10, //threshold (1-100)
    5, //scan time (1-100)
    40, //mask time (1-100)
    20, //rim sensitivity (1-100)
    3,  //rim threshold (1-100)
    3,  //curve type (0-4)
    38, //note (0-127)
    37  //note of cross stick (0-127)
};

byte HIHAT[7] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan start
    30,  //scan end
    46,  //note of open
    42,  //note of close
    3
};

byte HIHAT_PEDAL[7] = {
    100,  //sensitivity
    15,  //threshold
    5,  //scan start
    10,  //scan end
    10,  //pedal sensitivity
    44,  //note of pedal
    30, //note threshold
};

byte PADS[5]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    1,   //curve type (0-4)
};

byte PAD_NOTES[8] {
  41,
  43,
  45,
  47,
  48,
  49,
  50,
  51,
};

HelloDrum kick(12);
HelloDrum snare(11, 10);
HelloDrum hihat(8);
HelloDrum hihatPedal(9);

HelloDrum pads[8] = {
  HelloDrum(0),
  HelloDrum(1),
  HelloDrum(2),
  HelloDrum(3),
  HelloDrum(4),
  HelloDrum(5),
  HelloDrum(6),
  HelloDrum(7),
};


void setup()
{
  kick.setCurve(KICK[5]);
  snare.setCurve(SNARE[6]);
  hihat.setCurve(HIHAT[6]);

  for (int i = 0; i < 8; i++) {
    pads[i].setCurve(PADS[4]);
  }
}

void loop()
{
  kick.singlePiezo(KICK[0], KICK[1], KICK[2], KICK[3]);
  snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]);
  hihat.HH(HIHAT[0], HIHAT[1], HIHAT[2], HIHAT[3]);
  hihatPedal.hihatControl(HIHAT_PEDAL[0], HIHAT_PEDAL[1], HIHAT_PEDAL[2], HIHAT_PEDAL[3], HIHAT_PEDAL[4]);

  for (int i = 0; i < 8; i++) {
    pads[i].singlePiezo(PADS[0], PADS[1], PADS[2], PADS[3]);
  }

  // Kick

  if (kick.hit == true)
  {
    usbMIDI.sendNoteOn(KICK[4], kick.velocity, MIDI_CHANNEL);
    usbMIDI.sendNoteOff(KICK[4], 0, MIDI_CHANNEL);
  }

  // Snare

  if (snare.hit == true)
  {
    usbMIDI.sendNoteOn(SNARE[7], snare.velocity, MIDI_CHANNEL);
    usbMIDI.sendNoteOff(SNARE[7], 0, MIDI_CHANNEL);
  }
  else if (snare.hitRim == true)
  {
    usbMIDI.sendNoteOn(SNARE[8], snare.velocity, MIDI_CHANNEL);
    usbMIDI.sendNoteOff(SNARE[8], 0, MIDI_CHANNEL);
  }

  // HiHats

  if (hihat.hit == true)
  {
    if (hihatPedal.openHH == true)
    {
      usbMIDI.sendNoteOn(HIHAT[4], hihat.velocity, MIDI_CHANNEL);
      usbMIDI.sendNoteOff(HIHAT[4], 0, MIDI_CHANNEL);
    }
    else if (hihatPedal.closeHH == true)
    {
      usbMIDI.sendNoteOn(HIHAT[5], hihat.velocity, MIDI_CHANNEL);
      usbMIDI.sendNoteOff(HIHAT[5], 0, MIDI_CHANNEL);
    }
  }

  if (hihatPedal.hit == true)
  {
    usbMIDI.sendNoteOff(HIHAT[4], 0, MIDI_CHANNEL);
    if (hihatPedal.velocity > HIHAT_PEDAL[6])
    {
      usbMIDI.sendNoteOn(HIHAT_PEDAL[5], hihatPedal.velocity, MIDI_CHANNEL);
      usbMIDI.sendNoteOff(HIHAT_PEDAL[5], 0, MIDI_CHANNEL);
    }
  }

  // Pads

  for (int i = 0; i < 8; i++) {
    if (pads[i].hit == true)
    {
      usbMIDI.sendNoteOn(PAD_NOTES[i], pads[i].velocity, MIDI_CHANNEL);
      usbMIDI.sendNoteOff(PAD_NOTES[i], 0, MIDI_CHANNEL);
    }
  }
}