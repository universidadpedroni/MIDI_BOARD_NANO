#include <Arduino.h>
#include <config.h>
#include <Bounce2.h>
#include <midiConstants.h>
#include <nemesisConstants.h>
#include <RC5Constants.h>
#include <SoftwareSerial.h>


#if PAGES_AND_BUTTONS
  Bounce *Page = new Bounce[NUM_PAGE];
#endif
Bounce *Button = new Bounce[NUM_BUTTON];


int pageIndex = 0;
int buttonIndex = 0;
int lastbuttonIndex = 0;

MidiMessage midiMessage[NUM_PAGE][NUM_BUTTON];
SoftwareSerial SerialMidi(MIDI_RX,MIDI_TX);

#define len(arr) sizeof (arr)/sizeof (arr[0])

// Versión sin paginado
void loadMidiMessagesVer3(){
  //************************************************//
  // BOSS RC5 CC
  // PAGE 0 : RC5
  // Pag 0 BT 0
  midiMessage[0][0].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][0].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][0].param = CC_TAP_TEMPO;
  midiMessage[0][0].value = 127;
  midiMessage[0][0].sendZero = true;
  midiMessage[0][0].toggle = false; 

  // Pag 0 BT 1
  midiMessage[0][1].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][1].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][1].param = CC_RHYTHM_P_S;
  midiMessage[0][1].value = 127;
  midiMessage[0][1].sendZero = true;
  midiMessage[0][1].toggle = false; 

  // Pag 0 BT 1
  midiMessage[0][2].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][2].param = CC_VARIATION;
  midiMessage[0][2].value = 127;
  midiMessage[0][2].sendZero = false;  
  midiMessage[0][2].toggle = true;  

  // Pag 0 BT 3
  midiMessage[0][3].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][3].param = CC_RHY_PART_2;
  midiMessage[0][3].value = 0;
  midiMessage[0][3].sendZero = false;
  midiMessage[0][3].toggle = true; 


  // Pag 0 BT 4
  midiMessage[0][4].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][4].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][4].param = CC_RHY_PART_1;
  midiMessage[0][4].value = 0;
  midiMessage[0][4].sendZero = false;
  midiMessage[0][4].toggle = true; 

  // Pag 2 BT 0
  midiMessage[0][5].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][5].CC_PC = MIDI_CH_PRGM_CAHNGE;
  midiMessage[0][5].param = MIDI_CH_PRGM_CAHNGE;
  midiMessage[0][5].value = progNumber;
  midiMessage[0][5].sendZero = false;
  midiMessage[0][5].toggle = false; 

   // Pag 2 BT 1
  midiMessage[0][6].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][6].CC_PC = MIDI_CH_PRGM_CAHNGE;
  midiMessage[0][6].param = MIDI_CH_PRGM_CAHNGE;
  midiMessage[0][6].value = progNumber;
  midiMessage[0][6].sendZero = false;  
  midiMessage[0][6].toggle = false;  
 
}




void loadMidiMessagesVer2(){
  //************************************************//
  // BOSS RC5 CC
  // PAGE 0 : RC5
  // Pag 0 BT 0
  midiMessage[0][0].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][0].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][0].param = CC_TAP_TEMPO;
  midiMessage[0][0].value = 127;
  midiMessage[0][0].sendZero = true;
  midiMessage[0][0].toggle = false; 

   // Pag 0 BT 1
  midiMessage[0][1].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][1].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][1].param = CC_TRK_PLY_STP;
  midiMessage[0][1].value = 127;
  midiMessage[0][1].sendZero = true;  
  midiMessage[0][1].toggle = false; 

  // Pag 0 BT 2
  midiMessage[0][2].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][2].param = CC_RHYTHM_P_S;
  midiMessage[0][2].value = 127;
  midiMessage[0][2].sendZero = true;
  midiMessage[0][2].toggle = false; 

   // Pag 0 BT 3
  midiMessage[0][3].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][3].param = CC_VARIATION;
  midiMessage[0][3].value = 127;
  midiMessage[0][3].sendZero = false;  
  midiMessage[0][3].toggle = true;  

  //*************************************************//
  // PAGE 1 : RC5
  // Pag 1 BT 0
  midiMessage[1][0].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][0].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][0].param = CC_RHY_PART_1;
  midiMessage[1][0].value = 0;
  midiMessage[1][0].sendZero = false;
  midiMessage[1][0].toggle = true; 

  // Pag 1 BT 1
  midiMessage[1][1].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][1].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][1].param = CC_RHY_PART_2;
  midiMessage[1][1].value = 0;
  midiMessage[1][1].sendZero = false;
  midiMessage[1][1].toggle = true; 

  // Pag 1 BT 2
  midiMessage[1][2].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][2].param = CC_RHY_PART_3;
  midiMessage[1][2].value = 0;
  midiMessage[1][2].sendZero = false;
  midiMessage[1][2].toggle = true; 
  
  // Pag 1 BT 3
  midiMessage[1][3].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][3].param = CC_RHY_PART_4;
  midiMessage[1][3].value = 0;
  midiMessage[1][3].sendZero = false;
  midiMessage[1][3].toggle = true; 
  
  // PAGE 3: BOSS PC and NEMESIS CC
  // PAGE 2
  // Pag 2 BT 0
  midiMessage[2][0].Channel = RC5_MIDI_CHANNEL;
  midiMessage[2][0].CC_PC = MIDI_CH_PRGM_CAHNGE;
  midiMessage[2][0].param = MIDI_CH_PRGM_CAHNGE;
  midiMessage[2][0].value = progNumber;
  midiMessage[2][0].sendZero = false;
  midiMessage[2][0].toggle = false; 

   // Pag 2 BT 1
  midiMessage[2][1].Channel = RC5_MIDI_CHANNEL;
  midiMessage[2][1].CC_PC = MIDI_CH_PRGM_CAHNGE;
  midiMessage[2][1].param = MIDI_CH_PRGM_CAHNGE;
  midiMessage[2][1].value = progNumber;
  midiMessage[2][1].sendZero = false;  
  midiMessage[2][1].toggle = false;  

   // Pag 2 BT 2
  midiMessage[2][2].Channel = NEMESIS_MIDI_CHANNEL;
  midiMessage[2][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[2][2].param = CC_PRESET_UP;
  midiMessage[2][2].value = 127;
  midiMessage[2][2].sendZero = false;
  midiMessage[2][2].toggle = false;    

   // Pag 2 BT 3
  midiMessage[2][3].Channel = NEMESIS_MIDI_CHANNEL;
  midiMessage[2][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[2][3].param = CC_PRESET_DOWN;
  midiMessage[2][3].value = 127;
  midiMessage[2][3].sendZero = false;
  midiMessage[2][3].toggle = false; 

}


void loadMidiMessagesDefault(){
  // PAGE 0 : RC5
  // Pag 0 BT 0
  midiMessage[0][0].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][0].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][0].param = CC_TAP_TEMPO;
  midiMessage[0][0].value = 127;
  midiMessage[0][0].sendZero = true;
  midiMessage[0][0].toggle = false; 

   // Pag 0 BT 1
  midiMessage[0][1].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][1].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][1].param = CC_TRK_PLY_STP;
  midiMessage[0][1].value = 127;
  midiMessage[0][1].sendZero = true;  
  midiMessage[0][1].toggle = false;  

   // Pag 0 BT 2
  midiMessage[0][2].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][2].param = CC_MEMORY_DEC;
  midiMessage[0][2].value = 127;
  midiMessage[0][2].sendZero = true;
  midiMessage[0][2].toggle = false;    

   // Pag 0 BT 3
  midiMessage[0][3].Channel = RC5_MIDI_CHANNEL;
  midiMessage[0][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[0][3].param = CC_MEMORY_INC;
  midiMessage[0][3].value = 127;
  midiMessage[0][3].sendZero = true;
  midiMessage[0][3].toggle = false;
  //*************************************************//
  // PAGE 1 : RC5
  // Pag 1 BT 0
  midiMessage[1][0].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][0].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][0].param = CC_RHYTHM_P_S;
  midiMessage[1][0].value = 127;
  midiMessage[1][0].sendZero = true;
  midiMessage[1][0].toggle = false; 

   // Pag 1 BT 1
  midiMessage[1][1].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][1].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][1].param = CC_VARIATION;
  midiMessage[1][1].value = 127;
  midiMessage[1][1].sendZero = false;  
  midiMessage[1][1].toggle = true;  

   // Pag 1 BT 2
  midiMessage[1][2].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][2].param = CC_RHY_PART_2;
  midiMessage[1][2].value = 0;
  midiMessage[1][2].sendZero = false;
  midiMessage[1][2].toggle = true;    

   // Pag 0 BT 3
  midiMessage[1][3].Channel = RC5_MIDI_CHANNEL;
  midiMessage[1][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[1][3].param = CC_RHY_PART_3;
  midiMessage[1][3].value = 0;
  midiMessage[1][3].sendZero = false;
  midiMessage[1][3].toggle = true;
  //*************************************************//
  
  // PAGE 2
  // Pag 2 BT 0
  midiMessage[2][0].Channel = NEMESIS_MIDI_CHANNEL;
  midiMessage[2][0].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[2][0].param = CC_TEMPO_DIVISION;
  midiMessage[2][0].value = TEMPO_DIVISION[0];
  midiMessage[2][0].sendZero = false;
  midiMessage[2][0].toggle = true; 

   // Pag 2 BT 1
  midiMessage[2][1].Channel = NEMESIS_MIDI_CHANNEL;
  midiMessage[2][1].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[2][1].param = CC_OCTAVE_SHIFT_CONTROL;
  midiMessage[2][1].value = OCTAVES[0];
  midiMessage[2][1].sendZero = false;  
  midiMessage[2][1].toggle = true;  

   // Pag 2 BT 2
  midiMessage[2][2].Channel = NEMESIS_MIDI_CHANNEL;
  midiMessage[2][2].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[2][2].param = CC_PRESET_UP;
  midiMessage[2][2].value = 127;
  midiMessage[2][2].sendZero = false;
  midiMessage[2][2].toggle = false;    

   // Pag 2 BT 3
  midiMessage[2][3].Channel = NEMESIS_MIDI_CHANNEL;
  midiMessage[2][3].CC_PC = MIDI_CH_CTRL_CHANGE;
  midiMessage[2][3].param = CC_PRESET_DOWN;
  midiMessage[2][3].value = 127;
  midiMessage[2][3].sendZero = false;
  midiMessage[2][3].toggle = false;          
}

void checkPage(){
#if PAGES_AND_BUTTONS
  for (int i = 0; i < NUM_PAGE; i++)
  {
    Page[i].update();
    if (Page[i].fell())
    {
      pageIndex = i;
      
    }
      
  }
#endif
}

void checkButton(){
  for (int i = 0; i < NUM_BUTTON; i++)
  {
    Button[i].update();
    if (Button[i].fell())
    {
      buttonIndex = i;
      lastbuttonIndex = 99;   // Por si se presionan dos veces el mismo botón
    }
      
  }
}

// plays a MIDI note or Control change..  Doesn't check to see that
// cmd is greater than 127, or that data values are  less than 127:
// Examples: 
// cmd: NOTE_ON, data1: pitch, data2: 0 -127
// cmd: NOTE_OFF, data1: pitch, data2: 0
// cmd: CONTROL_CHANGE, data1: SUSTAIN, data2: 0 - 127
void sendMIDI(int cmd, int data1, int data2) 
{
  SerialMidi.write(cmd);
	SerialMidi.write(data1);
	SerialMidi.write(data2);

	 //USER FRIENDLY
   
  Serial.print("MIDI: ");
	Serial.print(cmd);
	Serial.print("\t");
	Serial.print(data1);
	Serial.print("\t");
	Serial.println(data2);

  //Serial.write(cmd);
  //Serial.write(data1);
  //Serial.write(data2);

  // Actualizaciones y cambios de estados
  // TODO: Tengo que ver que hago con las subdivisiones del Nemesis
  //if (midiMessage[pageIndex][buttonIndex].toggle)
  //  midiMessage[pageIndex][buttonIndex].value == 127 ? midiMessage[pageIndex][buttonIndex].value = 0 : midiMessage[pageIndex][buttonIndex].value = 127;
}


void sendMessage(){
  
  if (lastbuttonIndex != buttonIndex){
    parpadearG = true;
    // Verifica si es el pulsador de PC del RC5
    #if PAGES_AND_BUTTONS
    if(pageIndex == 2 && buttonIndex == 0){
      progNumber < 98? progNumber++ : progNumber = 0;
      midiMessage[2][0].value = progNumber;
    }
    if(pageIndex == 2 && buttonIndex == 1){
      progNumber > 0? progNumber-- : progNumber = 98;
      midiMessage[2][1].value = progNumber;
    } 
    #else
    if(pageIndex == 0 && buttonIndex == 5){
      progNumber < 98? progNumber++ : progNumber = 0;
      midiMessage[0][5].value = progNumber;
    }
    if(pageIndex == 0 && buttonIndex == 6){
      progNumber > 0? progNumber-- : progNumber = 98;
      midiMessage[0][6].value = progNumber;
    }
    #endif
        // Enviar Mensaje
    sendMIDI(midiMessage[pageIndex][buttonIndex].CC_PC| char(midiMessage[pageIndex][buttonIndex].Channel),
             midiMessage[pageIndex][buttonIndex].param,
             midiMessage[pageIndex][buttonIndex].value );
    delay(1);
    // Verificar si hay que enviar un 0
    if(midiMessage[pageIndex][buttonIndex].sendZero)
      sendMIDI(midiMessage[pageIndex][buttonIndex].CC_PC| char(midiMessage[pageIndex][buttonIndex].Channel),
             midiMessage[pageIndex][buttonIndex].param,
             0);
    // Verificar si hay que cambiar el valor
    if(midiMessage[pageIndex][buttonIndex].toggle)
      midiMessage[pageIndex][buttonIndex].value == 127? midiMessage[pageIndex][buttonIndex].value = 0 : midiMessage[pageIndex][buttonIndex].value = 127;         

    // Rutinas para el Nemesis
    

    lastbuttonIndex = buttonIndex;
  }
  

}

void parpadearSwitch(int pin, unsigned long interval)
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

void parpadearPage(int pin, unsigned long interval)
{
  static int cuentaParpadeo = 0;
  static unsigned long previousMillis = 0;        // will store last time LED was updated
	//const long interval = 1000;           // interval at which to blink (milliseconds)
	unsigned long currentMillis = millis();
	static bool estadoPin=false;
	if (!parpadearG)
  {
    
    if(currentMillis - previousMillis > interval)  
	  {
      previousMillis = currentMillis;
      if(cuentaParpadeo < 2 * (pageIndex + 1))
      {
        estadoPin==false? estadoPin=true : estadoPin=false;
		    digitalWrite(pin, estadoPin);
      }
      else
      {
        digitalWrite(pin,LOW);
      }
    }
    cuentaParpadeo == 7? cuentaParpadeo = 0: cuentaParpadeo ++;
    
    

  }
	
}

void setup() {
  delay(1000);
  Serial.begin(BAUDRATE);
  SerialMidi.begin(BAUDRATE_MIDI);

  Serial.println("Hey Ho Lets Go!");
  
#if PAGES_AND_BUTTONS  
  for (int i = 0; i < NUM_PAGE; i++) {
    Page[i].attach(PIN_PAGE[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    Page[i].interval(25);              // interval in ms
  }
#endif
  

  for (int i = 0; i < NUM_BUTTON; i++) {
    Button[i].attach( PIN_BUTTON[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    Button[i].interval(25);              // interval in ms
  }

#if PAGES_AND_BUTTONS 
  loadMidiMessagesVer2();
  //loadMidiMessagesDefault();
#else
  loadMidiMessagesVer3();
  

#endif
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
#if PAGES_AND_BUTTONS  
  // Ajusto la memoria del RC5 a la primera posición
  sendMIDI(midiMessage[2][0].CC_PC| char(midiMessage[2][0].Channel),
             midiMessage[2][0].param,
             midiMessage[2][0].value );
#endif
  Serial.println(F("Setup Finished"));
  
}

void loop() {
#if PAGES_AND_BUTTONS 
  checkPage();
  parpadearPage(PIN_LED_R,250);
#endif
  
  checkButton();
  sendMessage();
  parpadearSwitch(PIN_LED_G,100);
  

  //delay(10);
}