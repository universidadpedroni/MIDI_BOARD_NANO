#include <Arduino.h>
#include <config.h>
#include "switchesFunc.h"
#include <midiConstants.h>
#include <nemesisConstants.h>
#include <RC5Constants.h>
#include <ACS1Cosntants.h>
#include <SoftwareSerial.h>

int RC5loopNumber = 0;

SoftwareSerial SerialMidi(MIDI_RX,MIDI_TX);

mySwitch mySw[NUM_SWITCHES];


void sendMIDI(int switchIndex)
{
  int ZERO = 0;
  // plays a MIDI note or Control change..  Doesn't check to see that
  // cmd is greater than 127, or that data values are  less than 127:
  // Examples: 
  // cmd: NOTE_ON, data1: pitch, data2: 0 -127
  // cmd: NOTE_OFF, data1: pitch, data2: 0
  // cmd: CONTROL_CHANGE, data1: SUSTAIN, data2: 0 - 127
  SerialMidi.write(mySw[switchIndex].CC_or_PC | (mySw[switchIndex].midiChannel));
	SerialMidi.write(mySw[switchIndex].param);
  // Los cambios de Loop del RC5 son un caso especial.
  if(switchIndex == 1)
  {
    RC5loopNumber < 98? RC5loopNumber++ : RC5loopNumber = 0;
    SerialMidi.write(RC5loopNumber);
  }
  else if (switchIndex == 0)
  {
    RC5loopNumber > 0? RC5loopNumber-- : RC5loopNumber = 98;
    SerialMidi.write(RC5loopNumber);
  } 
  //else if(switchIndex == 5){  // Los cambios de Preset del ACS1 también son un caso especial
  //  ACS1PresetNumber < 2? ACS1PresetNumber ++: ACS1PresetNumber = 0;
  //  SerialMidi.write(ACS1PresetNumber);
  //  Serial.print(mySw[switchIndex].midiChannel); Serial.print(","); Serial.println(ACS1PresetNumber);

  //} 
  else
  {
    SerialMidi.write(mySw[switchIndex].value);
  }
  if (mySw[switchIndex].sendZero){
    SerialMidi.write(mySw[switchIndex].CC_or_PC | (mySw[switchIndex].midiChannel));
	  SerialMidi.write(mySw[switchIndex].param);
    SerialMidi.write(ZERO);
  } 
  if (mySw[switchIndex].toggle) {
    mySw[switchIndex].value == 127? mySw[switchIndex].value = 0 : mySw[switchIndex].value = 127;
    Serial.print("MIDI Channel: "); Serial.println(mySw[switchIndex].midiChannel + 1);
    Serial.print("Val: "); Serial.println(mySw[switchIndex].value);
  }
}

void parpadearGreen(int pin, unsigned long interval)
{
  static int cuentaParpadeo = 0;
  static unsigned long previousMillis = 0;        // will store last time LED was updated
	//const long interval = 1000;           // interval at which to blink (milliseconds)
	unsigned long currentMillis = millis();
	static bool estadoPin=false;
	if (parpadearG)
  {
    if(currentMillis - previousMillis > interval) 
	  {
		  previousMillis = currentMillis;
		  estadoPin==false? estadoPin=true : estadoPin=false;
		  digitalWrite(pin, estadoPin);
      cuentaParpadeo += 1;
	  }
    if (cuentaParpadeo == 4)
    {
      parpadearG = false;
      cuentaParpadeo = 0;
    }

  }
	
}

void parpadearRed(int pin, unsigned long interval)
{
  static int cuentaParpadeo = 0;
  static unsigned long previousMillis = 0;        // will store last time LED was updated
	//const long interval = 1000;           // interval at which to blink (milliseconds)
	unsigned long currentMillis = millis();
	static bool estadoPin=false;
	if (parpadearR)
  {
    if(currentMillis - previousMillis > interval) 
	  {
		  previousMillis = currentMillis;
		  estadoPin==false? estadoPin=true : estadoPin=false;
		  digitalWrite(pin, estadoPin);
      cuentaParpadeo += 1;
	  }
    if (cuentaParpadeo == 4)
    {
      parpadearR = false;
      cuentaParpadeo = 0;
    }

  }
	
}

// Inicialización de los switches MIDI
void mySwInit(){
  // Switch 0: RC5, Loop P/S
  mySw[2].init(PIN_SWITCH[0], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_TRK_PLY_STP, 127, true, false);
  // Switch 1: RC5, LOOP UP
  mySw[1].init(PIN_SWITCH[1], RC5_MIDI_CHANNEL, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, RC5loopNumber);
  // Switch 2: RC5, LOOP DOWN
  mySw[0].init(PIN_SWITCH[2], RC5_MIDI_CHANNEL, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, RC5loopNumber);
  // Switch 3: RC5, Rhythm P/S
  mySw[3].init(PIN_SWITCH[3], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_RHYTHM_P_S, 127, true, false);
  // Switch 4: RC5, Variation
  mySw[4].init(PIN_SWITCH[4], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_VARIATION, 127, false, true);
  // Switch 5: RC5 Rhy Part 2 
  mySw[5].init(PIN_SWITCH[5], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_RHY_PART_2, 0, false, true);
  // Switch 6: RC5 Rhy Part 3 
  mySw[6].init(PIN_SWITCH[6], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_TAP_TEMPO, 127, true, false);
  
  // Switch 3: NEMESIS, PROG DOWN ;
  //mySw[4].init(PIN_SWITCH[4], NEMESIS_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_PRESET_UP, 127);
  // Switch 2: NEMESIS, PROG UP;
  //mySw[3].init(PIN_SWITCH[3], NEMESIS_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_PRESET_DOWN, 127);
  
  
  // Switch 6: ACS1, PRESET
  //mySw[5].init(PIN_SWITCH[5], ACS1_MIDI_CHANNEL, MIDI_CH_PRGM_CHANGE, 0xFF, 127, false, false);
  // Switch 7: ACS1, BOOST
  //mySw[6].init(PIN_SWITCH[6], ACS1_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_BOOST, 127, false, true);

}

void setup() {
  delay(1000);
  Serial.begin(BAUDRATE);
  SerialMidi.begin(BAUDRATE_MIDI);

  Serial.println("Hey Ho Lets Go!");
  Serial.println(F("Soft Ver 2.0"));
  Serial.print(F("Fecha y Hora de Compilacion: ")); Serial.print(__DATE__); Serial.print(F(",")); Serial.println(__TIME__);
  
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  mySwInit();
  Serial.println(F("Setup Finished"));
  
  
}

void loop() {
  parpadearGreen(PIN_LED_G,250);
  parpadearRed(PIN_LED_R, 250);
  for(int i = 0; i < NUM_SWITCHES; i++){
    mySw[i].update();
    if(mySw[i].sendMidiNow){
      mySw[i].midiChannel == RC5_MIDI_CHANNEL? parpadearR = true: parpadearG = true;
      Serial.print(F("Pin Switch: "));
      Serial.println(i);
      sendMIDI(i);
      mySw[i].sendMidiNow = false;
           
    }
  }

  
}