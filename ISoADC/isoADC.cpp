/* Using an SPI ADC (e.g., the MCP3008)
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root
* directory for copyright and GNU GPLv3 license information.            */
//https://forum.arduino.cc/index.php?topic=53082.0
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
using namespace std;
//using namespace exploringBB;
#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

int readAnalog(int number){
   stringstream ss;
   ss << LDR_PATH << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

double  value=0;
double  avgvalue=0;
int main(int argc, char **argv){
double  measuredvolt=0;
int channel=atoi(argv[1]);
int samples=atoi(argv[2]);
int sampledelayms=atoi(argv[3]);
float refv=atof(argv[4]);//3.332
float m1=atof(argv[6]);
float c1=atof(argv[7]);


for(int i=0;i<samples;i++)
{

   // Use the 8-bits of the second value and the two LSBs of the first value
  value+=readAnalog(channel);
// combineValues(receive[1]&0b00001111, receive[2]);
}
avgvalue=value/(double)samples;
//measuredvolt=(refv*avgvalue)/4095.00;//(m1*refv*(double)avgvalue))/(double)4095.00)+c1;
//measuredvolt=measuredvolt*m1+c1;
measuredvolt=m1*(refv*((double)avgvalue)/(double)4095.00)+c1;
cout<<measuredvolt<<endl;
//cout<<"Avg= "<<avgvalue<<" ,value= "<<value<<" ,Calculated= "<<measuredvolt<<endl;
}
