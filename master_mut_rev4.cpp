#include<iostream>
#include<unistd.h> //for usleep
#include"GPIO.h"
using namespace exploringBB;
using namespace std;
int count=0;
#include <stdlib.h>     /* atoi */
int diff_ms(timeval t1, timeval t2)
{
    return (((t1.tv_sec - t2.tv_sec) * 1000000) +
            (t1.tv_usec - t2.tv_usec))/1000;
}
#include <sys/time.h>
time_t begin,end; // time_t is a datatype to store time values.
int masterCounter=0;
int main(int argc,char **argv){
 GPIO inMUTGPIO(112), inMasterGPIO(115);

count=atoi(argv[1]);

//time (&begin);

while(inMUTGPIO.getValue()==1);
for(int i=0;i<count;i++)
{

while(inMUTGPIO.getValue()==0)

{
while(inMasterGPIO.getValue()==0);
while(inMasterGPIO.getValue()==1);
masterCounter++;
}
while(inMUTGPIO.getValue()==1)
{
while(inMasterGPIO.getValue()==0);
while(inMasterGPIO.getValue()==1);
masterCounter++;

}

//cout<<i;///<<end;

}
cout<<"MasterCounter="<<masterCounter<<endl;
//time (&end); // note time after execution
//double difference = difftime (end,begin);
//printf ("\nTime taken for Master pulses %.2lf seconds.\n", difference );
/*   GPIO outGPIO(60), inGPIO(46);

   // Basic Output - Flash the LED 10 times, once per second
   outGPIO.setDirection(OUTPUT);
   for (int i=0; i<10; i++){
      outGPIO.setValue(HIGH);
      usleep(500000); //micro-second sleep 0.5 seconds
      outGPIO.setValue(LOW);
      usleep(500000);
   }
   // Basic Input example
   inGPIO.setDirection(INPUT);
   cout << "The value of the input is: "<< inGPIO.getValue() << endl;

   // Fast write to GPIO 1 million times
   outGPIO.streamOpen();
   for (int i=0; i<1000000; i++){
      outGPIO.streamWrite(HIGH);
      outGPIO.streamWrite(LOW);
   }
   outGPIO.streamClose();
*/
   return 0;
}
