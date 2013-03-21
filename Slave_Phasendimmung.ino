#include <lib_phase_cntrl.h>

#include <Arduino.h>
#include <EasyTransfer.h>

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  uint8_t blau1;
  uint8_t blau2;
  uint8_t weiss1;
  uint8_t weiss2;
  uint8_t weiss3;
};
//create object
EasyTransfer ET; 
RECEIVE_DATA_STRUCTURE mydata;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;


void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &Serial);
  cli();

  init_phase_cntrl();
  DimmerField[0]=0;
  DimmerField[1]= 0;
  DimmerField[2]= 255;				//some fixed vals for output
  DimmerField[3]= 255;				//ch0,1 are captured from DIPs
  DimmerField[4]= 255;
  // DimmerField[5]= 150;
  //DimmerField[6]= 200;
  //DimmerField[7]= 255;



  sei();
}

void loop(){
  //check and see if a data packet has come in. 
  if(ET.receiveData()){
    DimmerField[0]= mydata.weiss1;
    DimmerField[1]= mydata.weiss2;
    DimmerField[2]= mydata.weiss3;			
    DimmerField[3]= mydata.blau1;			
    DimmerField[4]= mydata.blau2;
  }

}




