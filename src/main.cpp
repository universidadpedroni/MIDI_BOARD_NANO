#include <Arduino.h>
#include <config.h>
#include "switchesFunc.h"
#include <midiConstants.h>
#include <nemesisConstants.h>
#include <RC5Constants.h>
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
  if(switchIndex == 0)
  {
    RC5loopNumber < 98? RC5loopNumber++ : RC5loopNumber = 0;
    SerialMidi.write(RC5loopNumber);
  }
  else if (switchIndex == 1)
  {
    RC5loopNumber > 0? RC5loopNumber-- : RC5loopNumber = 98;
    SerialMidi.write(RC5loopNumber);
  }
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
    //Serial.print("Val: ");
    //Serial.println(mySw[switchIndex].value);
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
  // Switch 0: RC5, LOOP UP
  mySw[0].init(PIN_SWITCH[0], RC5_MIDI_CHANNEL, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, RC5loopNumber);
  // Switch 1: RC5, LOOP DOWN
  mySw[1].init(PIN_SWITCH[1], RC5_MIDI_CHANNEL, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, RC5loopNumber);
  // Switch 2: NEMESIS, PROG UP;
  mySw[2].init(PIN_SWITCH[2], NEMESIS_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_PRESET_UP, 127);
  // Switch 3: NEMESIS, PROG DWN;
  mySw[3].init(PIN_SWITCH[3], NEMESIS_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_PRESET_DOWN, 127);
  // Switch 4: RC5, RHYTHM PLAY_STOP
  mySw[4].init(PIN_SWITCH[4], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_RHYTHM_P_S, 127, true, false);
  // Switch 6: RC5, VARIATION
  mySw[5].init(PIN_SWITCH[5], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_VARIATION, 127, false, true);
  // Switch 6: RC5, SNARE ON / OFF
  mySw[6].init(PIN_SWITCH[6], RC5_MIDI_CHANNEL, MIDI_CH_CTRL_CHANGE, CC_RHY_PART_2, 0, false, true);

}

void setup() {
  delay(1000);
  //Serial.begin(BAUDRATE);
  SerialMidi.begin(BAUDRATE_MIDI);

  //Serial.println("Hey Ho Lets Go!");
  
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  mySwInit();
  //Serial.println(F("Setup Finished"));
  //Serial.println(__TIME__);
}

void loop() {
  parpadearGreen(PIN_LED_G,250);
  parpadearRed(PIN_LED_R, 250);
  for(int i = 0; i < NUM_SWITCHES; i++){
    mySw[i].update();
    if(mySw[i].sendMidiNow){
      mySw[i].midiChannel == RC5_MIDI_CHANNEL? parpadearR = true: parpadearG = true;
      //Serial.print(parpadearR);
      //Serial.print("   ");
      //Serial.println(parpadearG);
      sendMIDI(i);
      mySw[i].sendMidiNow = false;
           
    }
  }

  
}