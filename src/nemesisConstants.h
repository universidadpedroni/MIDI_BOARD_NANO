#include <midiConstants.h>

// https://www.sourceaudio.net/uploads/1/1/5/1/115104065/nemesis_midi_implementation_1_01.pdf

const int NEMESIS_MIDI_CHANNEL = MIDI_CHANNEL_2;

const int CC_TEMPO_DIVISION = 42;
const int TEMPO_DIVISION[] = { 6,   // Quarter notes
                               7,   // Dotted 8ths
                               8};  // Swinged 8ths

const int CC_OCTAVE_SHIFT_CONTROL = 50;
const int OCTAVES[] = { 0,          // OCtave down
                        63,         // Unison
                        127};       // Octave Up

const int CC_PRESET_UP = 82;
const int CC_PRESET_DOWN = 80;

