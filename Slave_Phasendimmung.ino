/**

Uses a simple Arduino or ATMEGA8 with Arduino Bootloader to work as a
Dimmer using phase angle controlling ( Phasenanschnittsdimmung).

***************************************************************************
 This program is free software; you can redistribute it and/or 
 modify it under the terms of the GNU General Public License 
 as published by the Free Software Foundation; either version2 of 
 the License, or (at your option) any later version. 

 This program is distributed in the hope that it will be useful, 
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 General Public License for more details. 

 If you have no copy of the GNU General Public License, write to the 
 Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. 

 For other license models, please contact the author.



***************************************************************************

Overview over used Ports:
marked with stars: Used.

        	            |----------------|
		        ----| 1     U      28|----		A5 /SCL
Serial  D0 / RX	  ***	----| 2		   27|----		A4 /SDA 
Serial  D1 / TX   ***	----| 3		   26|----		A3 
        D2 / INT0	----| 4		   25|----		A2  
        D3 / INT1	----| 5		   24|----		A1  
        D4   		----| 6		   23|----		A0  
	          VCC	----| 7		   22|---- GND	 
	          GND	----| 8		   21|---- VCC	
	        	----| 9		   20|---- VCC
        		----| 10	   19|----		D13 /SCK
DF[0]   D5 	***	----| 11	   18|----		D12 /MISO
DF[1]   D6 	***	----| 12	   17|----		D11 /MOSI 
DF[2]   D7 	***	----| 13	   16|----		D10 /SS 
DF[3]   D8 	***	----| 14	   15|----	***	D9         DF[4]
		            |----------------|
**/

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



void setup(){
  Serial.begin(9600);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(mydata), &Serial);
  cli();

  init_phase_cntrl();
  DimmerField[0]= 255;
  DimmerField[1]= 255;
  DimmerField[2]= 255;				
  DimmerField[3]= 255;				
  DimmerField[4]= 255;

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




