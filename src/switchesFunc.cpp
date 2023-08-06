#include "switchesFunc.h"

void mySwitch::init(int pin, int MIDIChannel, int MIDI_CC_or_PC, int MIDIParam, int MIDIValue, bool SendZero, bool toggleValue){
    _pin = pin;
    _button.attach(_pin, INPUT_PULLUP);
    _button.interval(5);
    _button.update();
    _estadoActual = _button.read();
    _estadoAnterior = _estadoActual;

    
    midiChannel = MIDIChannel;
    CC_or_PC = MIDI_CC_or_PC;
    param = MIDIParam;
    value = MIDIValue;
    sendMidiNow = false;
    sendZero = SendZero;
    toggle = toggleValue;
}

void mySwitch::update(){
    _button.update();
    _estadoActual = _button.read();
    if(_estadoActual != _estadoAnterior){
        sendMidiNow = true;
        _estadoAnterior = _estadoActual;
        
    }
    
}