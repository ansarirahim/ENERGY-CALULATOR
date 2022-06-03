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
int channel=0;
int readAnalog(int number){
   stringstream ss;
   ss << LDR_PATH << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}
float multiplier;
double  value=0;
double  avgvalue=0;
float cfactor=1;
int main(int argc, char **argv){
float measuredvolt=0;
//int
 channel=atoi(argv[1]);
int samples=atoi(argv[2]);
int sampledelayms=atoi(argv[3]);
float refv=atof(argv[4]);//3.332
float constant=atof(argv[6]);;
multiplier=atof(argv[5]);
double temp=0;
cfactor=atof(argv[7]);
//old cfactor=atof(argv[7]);
//for(channel=0;channel<7;channel++){
value =0;
avgvalue=0;
///printf("\nchannel=%d,samples=%d,sampledelay=%d,refv=%f,,multiplier=%f,constant=%f,cfactor=%f\n",channel,sampledelayms,refv,multiplier,constant,cfactor);//
for(int i=0;i<samples;i++)
{

   // Use the 8-bits of the second value and the two LSBs of the first value
  temp=readAnalog(channel);
//printf("%d=%.3f\n",i,temp);
value+=temp;
// combineValues(receive[1]&0b00001111, receive[2]);
}
avgvalue=value/(double)samples;
//measuredvolt=refv*((double)avgvalue)/(double)4095.00;
///measuredvolt=(-(avgvalue-constant)/multiplier)*cfactor;//old eqp
measuredvolt=(avgvalue*multiplier+constant)*cfactor;;//(-0.0003*avgvalue+0.5547)*cfactor;
//cout<<"Avg= "<<avgvalue<<" ,value= "<<value<<" ,Calculated= "<<measuredvolt<<endl;
printf("%.3f\n\r",measuredvolt);//cout<<measuredvolt;
//if(channel<6)
//cout<<",";
//else
//cout<<endl;
//cout<<"Channel="<<channel<<" "<<measuredvolt<<" V"<<endl;
   //cout << "This is the value " << value << " out of ." << endl;
//   cout << "End of EBB SPI ADC Example" << endl;
}


