
//11.12.2021
//UNDER DEVELOPMENTE TILL DATE WE CAN READ RANGE FROM THE LOCATED FILES
//BALANCE=NEED TO EVALUATE RANGE FROM ADC VALUE AND THEN ON THIS BASIS WE NEED TO  EXTRACT M AND C VALUES AND FROM THESE WE NEED TO CALCULATE
//CALLIBRATED VALUE  
///////////////////////////////

//A. R. Ansari
//arm-linux-gnueabihf-g++ getBBB_ADC7.cpp -o getBBB_ADC7
//./getBBB_ADC7 <channel> <no of samples> <delay between samples in us> <enable min max display>
//following will continously read adc 
//./getBBB_ADC7 0 100 1 3
//follwing will read
//./getBBB_ADC7 0 100 1 2
/*
adc=534
adc=534
adc=534
MIN=534 MAX=535 AVG=534

*/

//follwing will read
//./getBBB_ADC7 0 100 1 1
//MIN=534 MAX=535 AVG=534
//following will read
//./getBBB_ADC7 0 
//534
#include <stdlib.h>
//#include <cstdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>

#include <iostream>
#include <algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
uint64_t avg,sum=0;//sampleAvg=0;
uint64_t delay=0;
unsigned int channel=0;
unsigned int min1,max1=0;
#define MAX_ARGUMENTS 5
#define MAX_BBB_ADC7_CHANNELS 6
#define SAMPLE_BUFFER 1000
int size=0;
//unsigned int min,max;
unsigned int  data[SAMPLE_BUFFER];

#define LDR_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"
///home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/cpt1/m
#define CPT_PATH "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/"

#define CPT_PATH_M "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/cpt1/m"
///$1/cpt$2/m"

#define CPT_PATH_RANGES "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/"
#define CPT_PATH_RANGE1 "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/range1"
#define CPT_PATH_RANGE2 "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/range2"
#define CPT_PATH_RANGE3 "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/range3"
#define CPT_PATH_RANGE4 "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/range4"
//#define CPT_PATH_RANGE1 "/home/debian/LinearCallibration-main/LinearCallibration-main/BBb_adc7/BBb_adc7_NOmux/0/range1"

#define  NO_OF_RANGES 4


typedef struct mandc{
float m;
float c;
} LineMandC;

LineMandC Line;
uint32_t Ranges[NO_OF_RANGES];
uint32_t getRange(uint32_t mychannel,uint32_t range)
{
uint32_t myrange;
 stringstream ssrange1;
//ss<<CPT_PATH_M;//<<chan<<"/"<<cptno<<"/m";
ssrange1<<CPT_PATH_RANGES<<mychannel<<"/range"<<range;//<<"/m";
 fstream fs;//range1;
   fs.open(ssrange1.str().c_str(), fstream::in);
   fs >> myrange;
   fs.close();

return myrange;
}
void  readMandC(uint32_t  chan,int cptno)
{



//uint32_t range[4];
float mvalue;
float cvalue;
 stringstream ss1;
//ss<<CPT_PATH_M;//<<chan<<"/"<<cptno<<"/m";
ss1<<CPT_PATH<<chan<<"/cpt"<<cptno<<"/c";
 fstream fs1;
   fs1.open(ss1.str().c_str(), fstream::in);
   fs1 >> cvalue;
   fs1.close();

cout<<"\nvalue of c="<<cvalue<<endl;
Line.m= mvalue;
Line.c=cvalue;

}
/*

float  CallibratedValue(uint32_t chan,uint32_t rawadc)
{
/////////
ss<<CPT_PATH<<chan<<"/cpt"<<cptno<<"/m";
 fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> mvalue;
   fs.close();

///////////


float mvalue;
 stringstream ss;
ss<<CPT_PATH<<chan<<"/cpt"<<cptno<<"/m";
 fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> mvalue;
   fs.close();

cout<<"\nvalue of m="<<mvalue<<endl;

float cvalue;
 stringstream ss1;
//ss<<CPT_PATH_M;//<<chan<<"/"<<cptno<<"/m";
ss<<CPT_PATH<<chan<<"/cpt"<<cptno<<"/c";
 fstream fs1;
   fs1.open(ss1.str().c_str(), fstream::in);
   fs1 >> cvalue;
   fs1.close();

cout<<"\nvalue of c="<<cvalue<<endl;
Line.m= mvalue;
Line.c=cvalue;
return ((float)Line.m*(float)rawadc+(float)Line.c)

}*/

void normalizeMinMaxAvg()//unsigned int  data[], int size,unsigned int& min, unsigned int& max, uint64_t& avg)
{int i=0;
 min1=data[i];
max1= data[i];
for (i=0; i < size; i++)
{
    //count++;  - no need for it, you already have size!
    sum += data[i];
    if ( data[i]>max1){
        max1 = data[i];
    }
    if (min1 > data[i]){
        min1 = data[i];
    }
}
avg = sum/size;
}

//int channel=0;


uint32_t readAnalog(uint32_t number){
   stringstream ss;
   ss << LDR_PATH << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}
//#define MAX_BBB_ADC7_CHANNELS 6
//#define SAMPLE_BUFFER 100
//int noofsamples=0;
//unsigned int min,max;
//unsigned int  samples[SAMPLE_BUFFER];
#define CHANNEL_INDEX 1
#define SAMPLES_INDEX 2
#define DELAY_INDEX 3
#define ENABLE_MIN_MAX_AVG_DISPLAY_INDEX 4
//#define M
#define INDEX_M 5 
#define INDEX_C 6

#define DISPLAY_ALL_BUFFER_DATA 2
#define DISPLAY_ADC_FOREVER 3
int enable_min_max_avg_display=0;




int main(int argc, char* argv[]){
//   cout << "Starting the readLDR program" << endl;


char *ptr=NULL;

channel=strtoul(argv[CHANNEL_INDEX],&ptr,10);






if(argc< MAX_ARGUMENTS)
{
cout<<readAnalog(channel)<<endl;
return 0;
}
size=atoi(argv[SAMPLES_INDEX]);
delay=strtoull(argv[DELAY_INDEX],&ptr,10);//atoi(argv[3]);//delay
enable_min_max_avg_display=atoi(argv[ENABLE_MIN_MAX_AVG_DISPLAY_INDEX]);
/////////m 

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

///////c


///cout<<"argc="<<argc<<endl;
if(channel>MAX_BBB_ADC7_CHANNELS)
{cout<<"NACK"<<endl;
return 0;
}
/////////////////////////////////////////////////////////////////////////////

uint8_t tempi;
for(tempi=1;tempi<5;tempi++)
{
Ranges[tempi-1]=getRange(channel,tempi);

}
cout<<"*******"<<endl;
for(tempi=0;tempi<4;tempi++)
cout<<"range["<<tempi<<"]="<<Ranges[tempi]<<endl;
cout<<"*******"<<endl;


/////////////////////////////////////////////////////////////////
if(DISPLAY_ADC_FOREVER==enable_min_max_avg_display)
{
while(1)
{
cout<<((float)readAnalog(channel))*m+c<<endl;
usleep(delay);//
}
}
else{
//cout<<"argc="<<argc<<endl;
for(int i=0;i<size;i++)
{   data[i] = readAnalog(channel);//atoi(argv[1]%7);//0);
usleep(delay);

if(enable_min_max_avg_display==DISPLAY_ALL_BUFFER_DATA)


cout<<"value="<<((float)data[i])*m+c<<endl;
}
normalizeMinMaxAvg ();
if(enable_min_max_avg_display)
cout<<"MIN="<<((float)min1)*m+c<<" MAX="<<((float)max1)*m+c<<" AVG="<<((float)avg)*m+c<<endl;
else
cout<<((float)avg)*m+c<<endl;
}


cout<<"VER 2"<<endl;

readMandC(channel,1);
readMandC(channel,2);
readMandC(channel,3);
readMandC(channel,4);



//cout << "MIN=" << min << "AVG=" <<avg<<"MAX="<<max<< endl;
//normalizeMinMaxAvg ();//ples, noofsamples, min, max, avg);
//    cout<<min<<"  "<<max<<" "<<avg<<endl;
//cout<<value<<endl;
   //cout << "The LDR value was " << value << " out of 4095." << endl;
   return 0;
}
