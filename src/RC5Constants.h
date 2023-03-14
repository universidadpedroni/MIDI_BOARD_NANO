#include <midiConstants.h>

//https://www.kraftmusic.com/media/ownersmanual/Boss_RC-5_Reference_Manual.pdf

const int RC5_MIDI_CHANNEL = MIDI_CHANNEL_1;
const int CC_TAP_TEMPO = 80;
const int CC_TRK_PLY_STP = 81;
const int CC_RHYTHM_P_S = 82;
const int CC_VARIATION = 83;

const int CC_RHY_PART_1 = 84;
const int CC_RHY_PART_2 = 85;
const int CC_RHY_PART_3 = 86;
const int CC_RHY_PART_4 = 87;

const int CC_MEMORY_INC = 81;
const int CC_MEMORY_DEC = 82;
//const int CC_TRK_UNDO = 83;
//const int CC_RHY_FILL = 85;

const int CC_RC5[] = {80, 81, 82, 83, 84, 85, 86, 87};
int progNumber = 0;