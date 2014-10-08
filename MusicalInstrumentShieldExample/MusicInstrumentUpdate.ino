/*
 2-12-2011
 Spark Fun Electronics 2011
 Nathan Seidle
 Updated to Arduino 1.01 by Marc "Trench" Tschudin
 
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 This code works with the VS1053 Breakout Board and controls the VS1053 in what is called Real Time MIDI mode. 
 To get the VS1053 into RT MIDI mode, power up the VS1053 breakout board with GPIO0 tied low, GPIO1 tied high.
 
 I use the NewSoftSerial library to send out the MIDI serial at 31250bps. This allows me to print regular messages
 for debugging to the terminal window. This helped me out a ton.
 
 5V : VS1053 VCC
 GND : VS1053 GND
 D3 (SoftSerial TX) : VS1053 RX
 D4 : VS1053 RESET
 
 Attach a headphone breakout board to the VS1053:
 VS1053 LEFT : TSH
 VS1053 RIGHT : RSH
 VS1053 GBUF : GND
 
 When in the drum bank (0x78), there are not different instruments, only different notes.
 To play the different sounds, select an instrument # like 5, then play notes 27 to 87.
 
 To play "Sticks" (31):
 talkMIDI(0xB0, 0, 0x78); //Bank select: drums
 talkMIDI(0xC0, 5, 0); //Set instrument number
 //Play note on channel 1 (0x90), some note value (note), middle velocity (60):
 noteOn(0, 31, 60);
 
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator
//int  instrument = 1;

void setup() {
  Serial.begin(9600);

  //Setup soft serial for MIDI control
  mySerial.begin(31250);

  //Reset the VS1053
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 127); //0xB0 is channel message, set channel volume to near max (127)
}

void loop() {




  //Demo Basic MIDI instruments, GM1
  //=================================================================
//  Serial.println("Basic Instruments");
  talkMIDI(0xB0, 0, 0x00); //Default bank GM1
  talkMIDI(0xC0, 100, 0); //Set instrument number. 0xC0 is a 1 data byte command
  talkMIDI(0xB1, 0, 0x78); //Default bank GM1
  talkMIDI(0xC1, 30, 0);
  talkMIDI(0xB2, 0, 0x00); //Default bank GM1
  talkMIDI(0xC2, 20, 0);
  //Change to different instrument

    //Serial.print(" Instrument: ");
    Serial.println(instrument, DEC);


    //Play notes from F#-0 (30) to F#-5 (90):
    for (note = 30 ; note < 80 ; note++) {
   //   Serial.print("N:");
     // Serial.println(note, DEC);
      
      //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
      noteOn(0, note, 127);
      delay(50);

      //Turn off the note with a given off/release velocity
      noteOff(0, note, 127);
      delay(50);
      
        noteOn(1, note, 127);
      delay(50);

      //Turn off the note with a given off/release velocity
      noteOff(1, note, 127);
      delay(50);
      
       noteOn(2, note, 127);
      delay(50);

      //Turn off the note with a given off/release velocity
      noteOff(2, note, 127);
      delay(50);
    }

    delay(100); //Delay between instruments
  }




//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  mySerial.write(cmd);
  mySerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    mySerial.write(data2);

  digitalWrite(ledPin, LOW);
}
