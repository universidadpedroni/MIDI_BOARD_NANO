#include <Arduino.h>

// BaudRate
const long BAUDRATE = 115200;
const long BAUDRATE_MIDI = 31250;
const int MIDI_TX = 3;
const int MIDI_RX = A0;

const int PIN_SWITCH[] = {9, 8, 10, 12, 7, 6, 11};
const int NUM_SWITCHES = sizeof(PIN_SWITCH) / sizeof(int);

const int PIN_LED_G = 4;
const int PIN_LED_R = 5;

bool parpadearG = false;           // variable para determinar si se debe hacer parpadear el led o no.
