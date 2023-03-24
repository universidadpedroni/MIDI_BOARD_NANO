#include <Arduino.h>

#define PAGES_AND_BUTTONS false

// BaudRate
const long BAUDRATE = 115200;
const long BAUDRATE_MIDI = 31250;
const int MIDI_TX = 3;
const int MIDI_RX = A0;

#if PAGES_AND_BUTTONS
const int PIN_PAGE[] = {7, 6, 11};
const int NUM_PAGE = 3;

const int PIN_BUTTON[] = {9, 8, 10, 12}; 
const int NUM_BUTTON = 4;
#else
const int NUM_PAGE = 1; // para que no se rompa midiMessage[NUM_PAGE][NUM_BUTTON]
const int PIN_BUTTON[] = {9, 8, 10, 12, 7, 6, 11};
const int NUM_BUTTON = sizeof(PIN_BUTTON) / sizeof(int);
#endif


const int PIN_LED_G = 4;
const int PIN_LED_R = 5;

bool parpadearG = false;           // variable para determinar si se debe hacer parpadear el led o no.



struct MidiMessage{
    int Channel;
    int CC_PC;          //Control Change or Program Change
    int param;
    int value;
    bool sendZero;      // Some parameters of the RC5 need to send a zero
    bool toggle;        // para cambiar entre 0 y 127.
};