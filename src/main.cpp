#include <Arduino.h>
#include <hellodrum.h>

#define MIDI_CHANNEL 0

byte KICK[6] = {
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    40,  //mask time (1-)
    36,  //note (0-127)
    1    //curve type (0-4)
};

byte SNARE[9] = {
    90,  //sensitivity (1-100)
    50,  //threshold (1-100)
    30,  //scan time (1-100)
    10,  //mask time (1-100)
    10,  //rim sensitivity (1-100)
    3,   //rim threshold (1-100)
    3,   //curve type (0-4)
    38,  //note (0-127)
    37   //note of cross stick (0-127)
};

byte HIHAT[6] = {
    100, //sensitivity
    10,  //threshold
    10,  //scan start
    30,  //scan end
    46,  //note of open
    42,  //note of close
};

byte HIHAT_PEDAL[7] = {
    90,  //sensitivity
    30,  //threshold
    60,  //scan start
    80,  //scan end
    20,  //pedal sensitivity
    44,  //note of pedal
    100, //note threshold
};

byte PAD[6] {
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    40,  //mask time (1-)
    41,  //note (0-127)
    1    //curve type (0-4)
};

HelloDrum kick(12);
HelloDrum snare(10, 11);
HelloDrum hihat(1);
HelloDrum hihatPedal(0);
HelloDrum pad1(2);

void setup()
{
  kick.setCurve(KICK[5]);
  snare.setCurve(SNARE[6]);
  pad1.setCurve(PAD[5]);
}

void loop()
{
  kick.singlePiezo(KICK[0], KICK[1], KICK[2], KICK[3]);
  snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]);
  hihat.HH(HIHAT[0], HIHAT[1], HIHAT[2], HIHAT[3]);
  hihatPedal.hihatControl(HIHAT_PEDAL[0], HIHAT_PEDAL[1], HIHAT_PEDAL[2], HIHAT_PEDAL[3], HIHAT_PEDAL[4]);
  pad1.singlePiezo(PAD[0], PAD[1], PAD[2], PAD[3]);

  if (kick.hit == true)
  {
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

  if (hihat.hit == true && !snare.hitRim)
  {
    if (hihatPedal.openHH == true)
    {
      usbMIDI.sendNoteOn(HIHAT[4], hihat.velocity, MIDI_CHANNEL); //(note, velocity, channel)
      usbMIDI.sendNoteOff(HIHAT[4], 0, MIDI_CHANNEL);
    }
    else if (hihatPedal.closeHH == true)
    {
      usbMIDI.sendNoteOn(HIHAT[5], hihat.velocity, MIDI_CHANNEL); //(note, velocity, channel)
      usbMIDI.sendNoteOff(HIHAT[5], 0, MIDI_CHANNEL);
    }
  }

  if (hihatPedal.hit == true)
  {
    usbMIDI.sendNoteOff(HIHAT[4], 0, MIDI_CHANNEL);

    if (hihatPedal.velocity > HIHAT_PEDAL[6]) {
      usbMIDI.sendNoteOn(HIHAT_PEDAL[5], hihatPedal.velocity, 10); //(note, velocity, channel)
      usbMIDI.sendNoteOff(HIHAT_PEDAL[5], 0, 10);
    }
  }
  
  if (pad1.hit == true)
  {
    usbMIDI.sendNoteOn(PAD[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD[4], 0, MIDI_CHANNEL);
  }
}