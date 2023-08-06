#ifndef SWITCHESFUNC_H
#define SWITCHESFUNC_H

#include <Arduino.h>
#include <Bounce2.h>
#include "midiConstants.h"

const int SWITCH_ESTADO_ABIERTO = 0;
const int SWITCH_ESTADO_CERRADO = 1;


class mySwitch{
    public:
        int midiChannel;
        int CC_or_PC;
        int param;
        int value;
        bool sendMidiNow;
        bool sendZero;
        bool toggle;
        void init(int pin, int MIDIChannel, int MIDI_CC_or_PC, int MIDIParam, int MIDIValue, bool SendZero = false, bool toggleValue = false);
        void update();
    private:
        int _pin;
        Bounce _button;
        int _estadoAnterior;
        int _estadoActual;
};

#endif
