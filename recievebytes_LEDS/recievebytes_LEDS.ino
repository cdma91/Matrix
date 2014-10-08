
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif


#define PIN 6 // Digital Pin 6 - this is where we connect, on the Arduino


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 8x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top left, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800); 
  


byte inByte;   // Where to store the Bytes read
byte inBytes[36]; // Where to store the array
int index = 0;// index of array
boolean started = false; //testing if serial has arrived
boolean ended = false;// testing if serial has ended
boolean everythingReturned = false; // if 36 numbers have been recieved

void setup()
{
  Serial.begin(9600);
   matrix.begin(); 
   matrix.setBrightness(40);
}

void loop()
{
     
    

  if(Serial.available() > 0)
  {  
    inByte = Serial.read(); // Read a Byte
    //Serial.println(inByte, DEC);
    if(inByte == 255) //255 is sent at the start of the packet
    {
      Serial.println("started");
      started = true;
      index = 0;
      inBytes[index] = '\0';
    }
    
      else if(inByte == 0) //0 is sent at the end of the packet
    {
      Serial.println("ended");
      ended = true;
    }
     else if(started = true)
    {
      inBytes[index] = inByte;
      index++;
 
    
      inBytes[index] = '\0';
      if (index >= 36)
      {
        Serial.println("36 Recieved");
        index = 0;
        everythingReturned = true;
      }
    }
    
  if(started && ended && everythingReturned)
     {
    started = false;
    ended = false;
    everythingReturned = false;
   
    
      int i;
      for (i = 0; i < 36; i = i + 1) {
        Serial.print(i);
        Serial.print(":");
        Serial.println(inBytes[i], DEC);
      }

  for(int i=0; i < 6; i++)
    {
       for(int j=0; j < 6; j++)
    {
         matrix.drawPixel(j,i,matrix.Color(inBytes[(i*6)+j],255,0));
         matrix.show();
    }
    }

    index = 0;
    inBytes[index] = '\0';
    Serial.println("Everything returned and Ended");
    
 
   
     
     
    }
  }

}
    
       
   

  
     


