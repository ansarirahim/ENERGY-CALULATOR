#include <iostream>
#include <sstream>
#include "SPIDevice.h"
#include "ASCII_TABLE5X7.h"
#include <cstdlib> 
	typedef unsigned char tByte;
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
 #define COL_START 0X0 
 #define COL_END 0X7F 
 #define BLACK 0XFF
 #define CLR 0X00
 #define SHAPE_UP 0x02+10
 #define SHAPE_DN 0x03+10
 #define SHAPE_TICK 0x04
 #define NO_OF_LINES 0x50
   #define LCDLASTROW 0X4C
   #define PAGES 20
   #define BARPATTERN 0xff
   #define PASS 1
#define FAIL 0	

   #define INVERT_PIXELS 0XA7
    #define ON_PIXELS 0XA5

	#define GRAY_SHADE0 0XD0// 
		#define GRAY_SHADE1 0XD1// 
			#define GRAY_SHADE2 0XD2// 
			#define GRAY_SHADE3 0XD3// 
			#define SET_FL 90//		9[4]

			#define SCROLL_LSB 0X40 //0X4X
			#define SCROLL_MSB 0X50 //0X5X

int main(int argc, char **argv){

//////////////////////
////
tByte Col_Lsb=0;
int j=0;
  	tByte Col_Msb=0;
	tByte Line=atoi(argv[1]);
tByte Lines=Line;
tByte Col=atoi(argv[2]);
//   tByte j=0;
					 if(Line>NO_OF_LINES-8)
					 Lines=0;
				else
				Lines=Line/4;
   if(Col>COL_END-7)
	 {
	 Col_Lsb=0;
	 Col_Msb=0x10;
	 Lines++;
	 }
	else
	{  
	Col_Lsb=0x0f&Col;
	Col_Msb=0x10|(Col>>4);
	}
	if(Lines>19)
	  Lines=0;
int k=0;int curs=0;
 SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
   busDevice->setSpeed(4000);      // Have access to SPI Device object
   busDevice->setMode(SPIDevice::MODE0);
/////////////////////////////
for(j=0;j<2;j++)
//Lines,j,Col_Lsb,Col_Msb);
{
//GLCD_Home
system("LCD_CMD");
//LCD_Char,Lines,j,Col_Lsb,Col_Msb);
setCursor[0]=PAGE_START+Lines+j;
setCursor[1]= Col_Lsb;
setCursor[2]= Col_Msb;
//
for(k=0;k<3;k++)
busDevice->write(setCursor[k]);
system("LCD_DATA");
//

for(curs=0;curs<7;curs++)
{
busDevice->write(TXT_M[argv[3][0]][j][curs]);
}


}
////////////////////
/*
   cout << "Starting EBB SPI ADC Example" << endl;
   SPIDevice *busDevice = new SPIDevice(1,0); //Using second SPI bus (both loaded)
   busDevice->setSpeed(4000);      // Have access to SPI Device object
   busDevice->setMode(SPIDevice::MODE0);
 system("LCD_CMD");
for(int i=0;i<12;i++)
busDevice->write(lcdInit[i]);
setCursor[0]=PAGE_START;
setCursor[1]= 0x0;
setCursor[2]= 0x10;
for(int i=0;i<3;i++)
busDevice->write(setCursor[i]);///lcdInit[i]);
system("CLEAR_LCD");
system("LCD_DATA");
////busDevice->write(dbf9todb9m,1024);
int curs;
int lin=0;
for(lin=0;lin<2;lin++)
{
for(curs=0;curs<7;curs++)
{
busDevice->write(TXT_M[argv[1][0]][lin][curs]);
}

}
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
}system("LCD_DATA");
busDevice->write(dbf9todb9m[i]);

}*/
busDevice->close();
//   cout << "Response bytes are " << (int)receive[1] << "," << (int)receive[2] << endl;
 
   // Use the 8-bits of the second value and the two LSBs of the first value
  // int value = combineValues(receive[1]&0b00000011, receive[2]);
   //cout << "This is the value " << value << " out of 1024." << endl;
   cout << "End of EBB SPI ADC Example" << endl;
}
