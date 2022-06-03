//A. R. Ansari
//arm-linux-gnueabihf-g++ getBBB_ADC7.cpp -o getBBB_ADC7
//25.08.2021 ver 1 rev1
//


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
#include <string>
#include <sstream>

#include <iostream>
#include <string>
using namespace std;
#include <string.h>
#include <cstdio>
#include<stdio.h>
#include <iostream>
#include <sstream>

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
using std::cout; using std::cin;
using std::endl; using std::string;
//using std::to_string;
using std::stringstream;
using std::cout; using std::cin;
using std::endl; using std::string;
string muxselectcmd="SET_MUX_";
#include <iostream>
#include <string>
using namespace std;
#include <string.h>
#include <cstdio>
#include<stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;
//using namespace exploringBB;
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

using patch::to_string;
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

//cout<<"argc="<<argc<<endl;
//if(argc== (MAX_ARGUMENTS+1))
{///cout<<"\nMux enabled"<<endl;
 if (argc > (MAX_ARGUMENTS))
    {
//cout<<"\nMux enabled"<<endl;
//        cout << "\nMux enabled" << endl;
stringstream tmp_stream;
tmp_stream << muxselectcmd << atoi(argv[MAX_ARGUMENTS])<<" &>/dev/null"<<endl;//"\r\n";
//cout<<cmdBuffer<<endl;
/*
sprintf(cmdBuffer,"SET_MUX_%s",argv[MAX_ARGUMENTS]);//
cout<<cmdBuffer<<endl;//"\nCmd="<< tmp_stream.str() << endl;///tmp_stream.c_str()<<endl;//muxselectcmd.c_str()<<endl;//
cout<<*/

system(tmp_stream.str().c_str());//muxselectcmd.c_str());//set_mux_channel);
usleep(10000);
    }



}

if(atoi(argv[ENABLE_MIN_MAX_AVG_DISPLAY_INDEX])==10)
cout<<"channel="<<channel<<"mux="<<argv[MAX_ARGUMENTS]<<"smaples="<<size<<"delay="<<delay<<"enableValue="<<argv[ENABLE_MIN_MAX_AVG_DISPLAY_INDEX]<<endl;

if(channel>MAX_BBB_ADC7_CHANNELS)
{cout<<"NACK"<<endl;
return 0;
}

if(DISPLAY_ADC_FOREVER==enable_min_max_avg_display)
{
while(1)
{
cout<<readAnalog(channel)<<endl;
usleep(delay);//
}
}
else{
//cout<<"argc="<<argc<<endl;
for(int i=0;i<size;i++)
{   data[i] = readAnalog(channel);//atoi(argv[1]%7);//0);
usleep(delay);

if(enable_min_max_avg_display==DISPLAY_ALL_BUFFER_DATA)
cout<<"adc="<<data[i]<<endl;
}
normalizeMinMaxAvg ();
if(enable_min_max_avg_display)
cout<<"MIN="<<min1<<" MAX="<<max1<<" AVG="<<avg<<endl;
else
cout<<avg<<endl;
}
//cout << "MIN=" << min << "AVG=" <<avg<<"MAX="<<max<< endl;
//normalizeMinMaxAvg ();//ples, noofsamples, min, max, avg);
//    cout<<min<<"  "<<max<<" "<<avg<<endl;
//cout<<value<<endl;
   //cout << "The LDR value was " << value << " out of 4095." << endl;
   return 0;
}
