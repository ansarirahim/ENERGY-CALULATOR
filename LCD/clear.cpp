#include <iostream>
#include <sstream>
#include "SPIDevice.h"
#include "ASCII_TABLE5X7.h"
#include <cstdlib> 

using namespace std;
using namespace exploringBB;
#define PAGE_START 0x6c 
short combineValues(unsigned char upper, unsigned char lower){
   return ((short)upper<<8)|(short)lower;
}
unsigned char setCursor[3];
unsigned char lcdInit[]={0xe2,0xf1,0x7f,0xc0,0x40,0x50,0x2b,0xeb,0x81,0x5f,0x89,0xaf};
unsigned char  dbf9todb9m[1024] = {

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 192, 192, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 192, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 192, 192, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 127, 31, 31, 63, 127, 255, 255, 127, 31, 31, 31, 127, 255, 255, 127, 31, 31, 31, 127, 255, 255, 127, 31, 31, 31, 127, 255, 255, 127, 31, 31, 31, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 252, 39, 1, 0, 0, 0, 0, 128, 192, 192, 128, 0, 0, 0, 128, 192, 192, 128, 0, 0, 0, 128, 192, 192, 128, 0, 0, 0, 192, 192, 192, 0, 0, 0, 0, 192, 192, 192, 0, 0, 0, 0, 0, 1, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 127, 255, 255, 255, 255, 255, 192, 128, 128, 128, 224, 255, 247, 192, 128, 128, 128, 224, 255, 255, 192, 128, 128, 128, 192, 255, 249, 192, 128, 128, 128, 224, 255, 255, 192, 128, 128, 128, 224, 255, 255, 255, 255, 255, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 255, 0, 0, 0, 0, 10, 127, 255, 255, 255, 30, 0, 26, 127, 255, 255, 127, 30, 0, 38, 127, 255, 255, 127, 42, 0, 127, 255, 255, 255, 63, 0, 0, 127, 255, 255, 255, 63, 0, 0, 0, 0, 253, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 63, 255, 255, 255, 255, 255, 255, 255, 255, 127, 63, 63, 127, 255, 255, 255, 127, 63, 63, 127, 255, 255, 255, 63, 63, 63, 255, 255, 255, 255, 63, 63, 63, 255, 255, 255, 255, 255, 255, 255, 255, 255, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 255, 0, 0, 0, 0, 0, 0, 0, 0, 128, 192, 128, 0, 0, 0, 128, 128, 128, 128, 0, 0, 0, 128, 192, 128, 0, 0, 0, 0, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 0, 208, 47, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 15, 255, 255, 255, 255, 255, 255, 225, 0, 0, 0, 128, 251, 255, 224, 0, 0, 0, 128, 249, 255, 192, 0, 0, 0, 192, 255, 255, 192, 0, 0, 0, 192, 255, 255, 255, 255, 255, 255, 255, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 29, 254, 0, 0, 0, 0, 0, 0, 127, 255, 255, 255, 254, 0, 4, 255, 255, 255, 255, 62, 0, 60, 255, 255, 255, 255, 20, 0, 126, 255, 255, 255, 255, 8, 0, 0, 0, 0, 0, 128, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 63, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 254, 128, 128, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 128, 224, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

}; 
int main(){
///   cout << "Starting EBB SPI ADC Example" << endl;
   SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
   busDevice->setSpeed(400000);      // Have access to SPI Device object
   busDevice->setMode(SPIDevice::MODE0);
 
/*   unsigned char send[3], receive[3];
   send[0] = 0b00000001; // The Start Bit followed
   // Set the SGL/Diff and D mode -- e.g., 1000 means single ended CH0 value
   send[1] = 0b10000000; // The MSB is the Single/Diff bit and it is followed by 000 for CH0
   send[2] = 0;          // This byte doesn't need to be set, just for a clear display
   busDevice->transfer(send, receive, 3);
*/
system("LCD_CMD");
for(int i=0;i<12;i++)
busDevice->write(lcdInit[i]);
setCursor[0]=PAGE_START;
setCursor[1]= 0x0;
setCursor[2]= 0x10;
for(int i=0;i<3;i++)
busDevice->write(setCursor[i]);///lcdInit[i]);
system("LCD_DATA");
////busDevice->write(dbf9todb9m,1024);
int curs;
int lin=0;
/*
for(int i=0;i<1024;i++)
{
if(i%0x80==0)
{
lin++;
system("LCD_CMD");
setCursor[0]=PAGE_START+lin;// 0x0;
setCursor[1]=0;
setCursor[2]= 0x10;
for(curs=0;curs<3;curs++)
busDevice->write(setCursor[curs]);
}
system("LCD_DATA");
busDevice->write(0);

}
*/

////////////
for(int j=0;j<20;j++)
{
for(int i=0;i<160;i++)
busDevice->write(0);


}
system("LCD_CMD");
setCursor[0]=PAGE_START;
setCursor[1]= 0x0;
setCursor[2]= 0x10;
for(int i=0;i<3;i++)
busDevice->write(setCursor[i]);
system("LCD_DATA");
///////////
busDevice->close();
//   cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << endl;
 
   // Use the 8-bits of the second value and the two LSBs of the first value
  // int value = combineValues(receive[1]&0b00000011, receive[2]);
   //cout << "This is the value " << value << " out of 1024." << endl;
//   cout << "End of EBB SPI ADC Example" << endl;
}