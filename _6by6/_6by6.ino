int Pin0 = A2;        // sensor attached to analog Pin0
int Pin1 = A3;            // sensor attached to analog Pin1
int Pin2 = A4;        // sensor attached to analog Pin2
int Pin3 = A5;        // sensor attached to analog Pin3
int Pin4 = A6;        // sensor attached to analog Pin4
int Pin5 = A7;        // sensor attached to analog Pin5

int dPin[] = {8, 9, 10, 11, 12, 13}; //declaration of the pins we will use; i is the position within the array; i = 0 corresponds to output 2
int i = 0;

int sensorValue0 = 0; //value read from line 0 of the sensor
int sensorValue1 = 1; //value read from line 1 of the sensor
int sensorValue2 = 2; //value read from line 2 of the sensor
int sensorValue3 = 3; //value read from line 3 of the sensor
int sensorValue4 = 4; //value read from line 4 of the sensor
int sensorValue5 = 5; //value read from line 5 of the sensor

int msensorValue0 = 0; // mapped value read from line 0 of the sensor
int msensorValue1 = 1; // mapped value read from line 1 of the sensor
int msensorValue2 = 2; // mapped value read from line 2 of the sensor
int msensorValue3 = 3; // mapped value read from line 3 of the sensor
int msensorValue4 = 4; // mapped value read from line 4 of the sensor
int msensorValue5 = 5; // mapped value read from line 5 of the sensor

void setup() {
  
  for (int i = 5; i >= 0 ; i--) {
pinMode(dPin[i], OUTPUT);             //declaration of pin[i] as an OUTPUT

pinMode (Pin0, INPUT);             //declaration of INPUT pins
pinMode (Pin1, INPUT);
pinMode (Pin2, INPUT);
pinMode (Pin3, INPUT);
pinMode (Pin4, INPUT);
pinMode (Pin5, INPUT);

}
  Serial.begin(9600);   //turn serial on
}

void loop(){
    Serial.write((byte)255); 

 for (int i = 5; i >= 0 ; i--) { 
                                  
  digitalWrite (dPin[i], HIGH); //turn row i on 
  sensorValue0 = analogRead (Pin5); //read value column 0
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(10);   
  sensorValue1 = analogRead (Pin4); //read value column 1
  delay(10);
  sensorValue2 = analogRead (Pin3); //read value column 2
  delay(10);
  sensorValue3 = analogRead (Pin2); //read value column 3
  delay(10);
  sensorValue4 = analogRead (Pin1); //read value column 4
  delay(10);
  sensorValue5 = analogRead (Pin0); //read value column 5
  delay(10);
  digitalWrite (dPin[i], LOW); //turn row i off 
  

  msensorValue0 = map (sensorValue0, 0, 1023, 254, 1);    //map all values read to a new range from 255 to 0
  msensorValue1 = map (sensorValue1, 0, 1023, 254, 1);
  msensorValue2 = map (sensorValue2, 0, 1023, 254, 1);
  msensorValue3 = map (sensorValue3, 0, 1023, 254, 1);
  msensorValue4 = map (sensorValue4, 0, 1023, 254, 1);
  msensorValue5 = map (sensorValue5, 0, 1023, 254, 1);
  
  msensorValue0 = constrain (msensorValue0, 1, 254);
  msensorValue1 = constrain (msensorValue1, 1, 254);
  msensorValue2 = constrain (msensorValue2, 1, 254);
  msensorValue3 = constrain (msensorValue3, 1, 254);
  msensorValue4 = constrain (msensorValue4, 1, 254);
  msensorValue5 = constrain (msensorValue5, 1, 254);
      
  Serial.write((byte)msensorValue0);   //print first value on the serial port
  Serial.write((byte)msensorValue1);   //print second value on the serial port
  Serial.write((byte)msensorValue2);
  Serial.write((byte)msensorValue3);
  Serial.write((byte)msensorValue4);
  Serial.write((byte)msensorValue5);
 
}
Serial.write((byte)0);
}
