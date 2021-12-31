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
    50, //threshold (1-100)
    5, //scan time (1-100)
    40, //mask time (1-100)
    10, //rim sensitivity (1-100)
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
    20,  //threshold
    5,  //scan start
    10,  //scan end
    10,  //pedal sensitivity
    44,  //note of pedal
    100, //note threshold
};

byte PAD_1[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    41,  //note (0-127)
    1,   //curve type (0-4)
};

byte PAD_2[6]{
    10, //sensitivity (1-100)
    50,  //threshold (1-100)
    50,  //scan time (1-)
    100,  //mask time (1-)
    43,  //note (0-127)
    4,   //curve type (0-4)
};

byte PAD_3[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    45,  //note (0-127)
    1,   //curve type (0-4)
};

byte PAD_4[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    47,  //note (0-127)
    1,   //curve type (0-4)
};

byte PAD_5[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    48,  //note (0-127)
    1,   //curve type (0-4)
};

byte PAD_6[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    49,  //note (0-127)
    1,   //curve type (0-4)
};

byte PAD_7[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    50,  //note (0-127)
    1,   //curve type (0-4)
};

byte PAD_8[6]{
    100, //sensitivity (1-100)
    50,  //threshold (1-100)
    10,  //scan time (1-)
    200,  //mask time (1-)
    51,  //note (0-127)
    1,   //curve type (0-4)
};

HelloDrum kick(12);
HelloDrum snare(11, 10);
HelloDrum hihat(1);
HelloDrum hihatPedal(0);
HelloDrum pad1(5);
HelloDrum pad2(4);
HelloDrum pad3(3);
HelloDrum pad4(2);
HelloDrum pad5(9);
HelloDrum pad6(8);
HelloDrum pad7(7);
HelloDrum pad8(6);

void setup()
{
  kick.setCurve(KICK[5]);
  snare.setCurve(SNARE[6]);
  hihat.setCurve(HIHAT[6]);
  pad1.setCurve(PAD_1[5]);
  pad2.setCurve(PAD_2[5]);
  pad3.setCurve(PAD_3[5]);
  pad4.setCurve(PAD_4[5]);
  pad5.setCurve(PAD_5[5]);
  pad6.setCurve(PAD_6[5]);
  pad7.setCurve(PAD_7[5]);
  pad8.setCurve(PAD_8[5]);
}

void loop()
{
  kick.singlePiezo(KICK[0], KICK[1], KICK[2], KICK[3]);
  snare.dualPiezo(SNARE[0], SNARE[1], SNARE[2], SNARE[3], SNARE[4], SNARE[5]);
  hihat.HH(HIHAT[0], HIHAT[1], HIHAT[2], HIHAT[3]);
  hihatPedal.hihatControl(HIHAT_PEDAL[0], HIHAT_PEDAL[1], HIHAT_PEDAL[2], HIHAT_PEDAL[3], HIHAT_PEDAL[4]);
  pad1.singlePiezo(PAD_1[0], PAD_1[1], PAD_1[2], PAD_1[3]);
  pad2.singlePiezo(PAD_2[0], PAD_2[1], PAD_2[2], PAD_2[3]);
  pad3.singlePiezo(PAD_3[0], PAD_3[1], PAD_3[2], PAD_3[3]);
  pad4.singlePiezo(PAD_4[0], PAD_4[1], PAD_4[2], PAD_4[3]);
  pad5.singlePiezo(PAD_5[0], PAD_5[1], PAD_5[2], PAD_5[3]);
  pad6.singlePiezo(PAD_6[0], PAD_6[1], PAD_6[2], PAD_6[3]);
  pad7.singlePiezo(PAD_7[0], PAD_7[1], PAD_7[2], PAD_7[3]);
  pad8.singlePiezo(PAD_8[0], PAD_8[1], PAD_8[2], PAD_8[3]);

  // Kick

  if (kick.hit == true)
  {
    usbMIDI.sendNoteOn(KICK[4], kick.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(KICK[4], 0, MIDI_CHANNEL);
  }

  // Snare

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

  // HiHats

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

    if (hihatPedal.velocity > HIHAT_PEDAL[6])
    {
      usbMIDI.sendNoteOn(HIHAT_PEDAL[5], hihatPedal.velocity, 10); //(note, velocity, channel)
      usbMIDI.sendNoteOff(HIHAT_PEDAL[5], 0, 10);
    }
  }

  // Pads

  if (pad1.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_1[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_1[4], 0, MIDI_CHANNEL);
  }

  else if (pad2.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_2[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_2[4], 0, MIDI_CHANNEL);
  }

  else if (pad3.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_3[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_3[4], 0, MIDI_CHANNEL);
  }

  else if (pad4.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_4[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_4[4], 0, MIDI_CHANNEL);
  }

  else if (pad5.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_5[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_5[4], 0, MIDI_CHANNEL);
  }

  else if (pad6.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_6[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_6[4], 0, MIDI_CHANNEL);
  }

  else if (pad7.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_7[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_7[4], 0, MIDI_CHANNEL);
  }

  else if (pad8.hit == true)
  {
    usbMIDI.sendNoteOn(PAD_8[4], pad1.velocity, MIDI_CHANNEL); //(note, velocity, channel)
    usbMIDI.sendNoteOff(PAD_8[4], 0, MIDI_CHANNEL);
  }
}