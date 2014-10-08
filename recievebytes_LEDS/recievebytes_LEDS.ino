
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
byte inBytes[36];
int index = 0;
boolean started = false;
boolean ended = false;
boolean everythingReturned = false;

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
    if(inByte == 255)
    {
      // Serial.println("started");
      started = true;
      index = 0;
      inBytes[index] = '\0';
    }
    
      else if(inByte == 0)
    {
      // Serial.println("ended");
      ended = true;
    }
     else if(started = true)
    {
      inBytes[index] = inByte;
      index++;
 
    
      inBytes[index] = '\0';
      if (index >= 36)
      {
        // Serial.println("36 Recieved");
        index = 0;
        everythingReturned = true;
      }
    }
    
  if(started && ended && everythingReturned)
     {
    started = false;
    ended = false;
    everythingReturned = false;
   
    // printing all the values
      int i;
      for (i = 0; i < 36; i = i + 1) {

        if ( inBytes[i] < 254 )
          { 
              Serial.print(inBytes[i], DEC); 
          } else { 
              Serial.print("___"); 
          }
        Serial.print("\t");
        // print values out in an array to visualise where the pressure is being appleid
      if ( (i+1) % 6 == 0 )
      {
         Serial.println();
      }
      }
      Serial.println();

  for(int i=0; i < 6; i++)
    {
       for(int j=0; j < 6; j++)
    {
         matrix.drawPixel(j,i,matrix.Color(255 - inBytes[(i*6)+j],255 - (i * 50), 255 - (j * 50)));   // read through the 6 x6 grid, indexing by i and j, where i is multiplied by 6 to offset in each row of 6, and j indexing into each row
         matrix.show();  
    }
    }

    index = 0;
    inBytes[index] = '\0';
    // Serial.println("Everything returned and Ended");
     
     
    }
  }

}
    
       
   

  
     


