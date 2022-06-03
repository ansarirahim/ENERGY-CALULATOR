//https://forum.arduino.cc/index.php?topic=53082.0
/* Using an SPI ADC (e.g., the MCP3008)
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root
* directory for copyright and GNU GPLv3 license information.            */
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <iostream>

// cstdlib is needed for atoi()
#include <cstdlib>

#include <iostream>
#include <string>
using namespace std;
#include <string.h>
#include <cstdio>
#include<stdio.h>
#include <iostream>
#include <sstream>
////#include "bus/SPIDevice.h"
#include <stdlib.h>
using namespace std;
using namespace exploringBB;
#define NO_OF_CHANNELS 32
#define SIZE_OF_CHANNEL_BUFFER 20
//char *channels[NO_OF_CHANNELS]
#include <string>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#include <iostream>
char set_mux_channel[SIZE_OF_CHANNEL_BUFFER];//="SET_MUX_";

/*
uint16_t MCP3208::analogRead(uint8_t pin) {
    uint8_t addr = 0b01100000 | ((pin & 0b111) << 2);
    digitalWrite(_cs, LOW);
    (void) spiTransfer(addr);
    uint8_t b1 = spiTransfer(0);
    uint8_t b2 = spiTransfer(0);
    digitalWrite(_cs, HIGH);

    return (b1 << 4) | (b2 >> 4);
}

int16_t MCP3208::analogReadDif(uint8_t pin) {
    uint8_t diff;
    uint8_t b1, b2;
    uint8_t addr = 0b01000000 | ((pin & 0b11) << 3);
    digitalWrite(_cs, LOW);
    (void) spiTransfer(addr);
    b1 = spiTransfer(0);
    b2 = spiTransfer(0);
    digitalWrite(_cs, HIGH);

    diff = (b1 << 4) | (b2 >> 4);
    if (diff > 0) {
        return diff;
    }
    addr = 0b01000100 | ((pin & 0b11) << 3);
    digitalWrite(_cs, LOW);
    (void) spiTransfer(addr);
    b1 = spiTransfer(0);
    b2 = spiTransfer(0);
    digitalWrite(_cs, HIGH);
    diff = (b1 << 4) | (b2 >> 4);
    return -diff;
}
*/
short combineValues(unsigned char upper, unsigned char lower){
   return ((short)upper<<8)|(short)lower;
}
/*
 byte commandMSB = b00000110;
 uint16_t commandBytes = (uint16_t) (commandMSB<<8|channel<<6);
 
 //Select ADC
 digitalWrite(9, LOW);
 //send start bit and bit to specify single or differential mode (single mode chosen here)
 SPI.transfer((commandBytes>>8) & 0xff);

 msb = SPI.transfer((byte)commandBytes & 0xff) & b00001111;
 lsb = SPI.transfer(0x00);
 
 digitalWrite(9,HIGH);
 

 // cast before shiting the byte
 return = ((uint16_t) msb) <<8 | lsb;
}

*/
#include <string>
#include <vector>
#include <sstream>

using std::cout; using std::cin;
using std::endl; using std::string;
//using std::to_string;
using std::stringstream;
using std::cout; using std::cin;
using std::endl; using std::string;
using patch::to_string;
string muxselectcmd="SET_MUX_";
#define INDEX_M 1
#define INDEX_C 2
#define INDEX_CHANNEL 3
#define INDEX_NO_OF_SAMPLES 4

int main(int argc, char **argv){




 std::string sLine;
 std::string sLine1;
ifstream infile(argv[INDEX_M]);

  if (infile.good())
  {
    //string sLine;
    getline(infile, sLine);
//    cout << sLine << endl;
  }

ifstream infile1(argv[INDEX_C]);

  if (infile1.good())
  {
    //string sLine;
    getline(infile1, sLine1);
  ///  cout << sLine1 << endl;
  }
float m =atof(sLine.c_str());// std::stof(sLine);
float c=  atof(sLine1.c_str());//std::stof(sLine1);



int channel=atoi(argv[INDEX_CHANNEL]);

				//stringstream tmp_stream;
				//tmp_stream << muxselectcmd << channel<<"&>/dev/null"<<endl;//"\r\n"; 
////cout<<"Cmd="<< tmp_stream.str() << endl;///tmp_stream.c_str()<<endl;//muxselectcmd.c_str()<<endl;//
			//system(tmp_stream.str().c_str());//muxselectcmd.c_str());//set_mux_channel);
			//usleep(1000);
cout<<value*m+c<<endl;
   //cout << "This is the value " << value << " out of ." << endl;
//   cout << "End of EBB SPI ADC Example" << endl;
}
