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







//cout << "MIN=" << min << "AVG=" <<avg<<"MAX="<<max<< endl;
//normalizeMinMaxAvg ();//ples, noofsamples, min, max, avg);
//    cout<<min<<"  "<<max<<" "<<avg<<endl;
//cout<<value<<endl;
   //cout << "The LDR value was " << value << " out of 4095." << endl;
   return 0;
}
