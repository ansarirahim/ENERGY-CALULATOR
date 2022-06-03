/* PRUSS program to drive a for RTC ERROR MEASUREMENT
*  in Linux userspace by sending an interrupt.
*  written by A. R. Anasri
*/
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <pthread.h>
#include <unistd.h>
#define PATH_COUNTS "/root/160718/countsP930"
#define PATH_BIN "/root/160718/512/P9_30/P930_P937_kwh_Pulses_10.bin"
//P930_kwh.bin"
//P930.bin"
#define PRU_NUM 0
#include <fstream>  
#include <iostream>
using std::cout;
using std::endl;
static void *pru0DataMemory;
static unsigned int *pru0DataMemory_int;
unsigned int  raw_counts;// = *(pru0DataMemory_int+2);
 unsigned int raw_countsP927;// = *(pru0DataMemory_int+3);
double ratio;
double error;
double error_ratio;
unsigned int mutk,masterk;
unsigned int noofpulses=0;
double master_energy;//=0.1*ratio;
double mut_energy;//=1.25*1;
double error_energy;//=master_energy-mut_energy;
double percent_error;//=(master_energy-mut_energy/master_energy)*100;
#define MAX_SAMPLES 1000
unsigned int rawCounts27[MAX_SAMPLES];
unsigned int rawCounts30[MAX_SAMPLES];
int noofsamples=0;
double  avgrawCounts27;
double  avgrawCounts30;
unsigned long long sumCounts27;
unsigned long long sumCounts30;
unsigned int maxCounts27;
unsigned int maxCounts30;
unsigned int minCounts30;
unsigned int minCounts27;
char cmdLCD[100];
int sample;
char pruCmd[40];
int  main (int argc, char **argv)
{
   if(getuid()!=0){
      printf("You must run this program as root. Exiting.\n");
      exit(EXIT_FAILURE);
   }
noofsamples=atoi(argv[1]);
sample=atoi(argv[2]);
//noofpulses=atoi(argv[1]);
//masterk=atoi(argv[2]);
//mutk=atoi(argv[3]);
//P930_P937_kwh_Pulses_10.p
////sprintf(pruCmd,"/root/160718/512/P9_30/P930_P937_kwh_Pulses_%d.bin",sample);
///printf("pru=%s",pruCmd);
   ////pthread_t thread;
printf("\n");
for(int no=0;no<noofsamples;no++)
{
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

   // Allocate and initialize memory
   prussdrv_init ();
   prussdrv_open (PRU_EVTOUT_0);
   prussdrv_open (PRU_EVTOUT_1);

   // Map PRU's INTC
   prussdrv_pruintc_init(&pruss_intc_initdata);
///// *(pru0DataMemory_int+2)=0;///pru0DataMemory=0;/////
   // Copy data to PRU memory - different way
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory);
   pru0DataMemory_int = (unsigned int *) pru0DataMemory;
   // Use the first 4 bytes for the number of samples
   *pru0DataMemory_int =noofpulses;//512;//32;// 500;
   // Use the second 4 bytes for the sample delay in ms
   *(pru0DataMemory_int+1) =0;///100;   // 2 milli seconds between samples

   // Load and execute binary on PRU
   prussdrv_exec_program (PRU_NUM,PATH_BIN);//pruCmd);//PATH_BIN);// 
/*   if(pthread_create(&thread, NULL, &threadFunction, NULL)){
       printf("Failed to create thread!");
   }*/
///sleep(1);
   int n = prussdrv_pru_wait_event (PRU_EVTOUT_0);
///   printf("PRU program completed, event number %d.\n", n);
   ////printf("The data that is in memory is:\n");
   ///printf("- the number of samples used is %d.\n", *pru0DataMemory_int);
   ///printf("- the time delay used is %d.\n", *(pru0DataMemory_int+1));
 raw_counts = *(pru0DataMemory_int+2);
 rawCounts30[no]=raw_counts;
 raw_countsP927 = *(pru0DataMemory_int+3);  
rawCounts27[no]=raw_countsP927;
ratio=((double)raw_counts)/((double)raw_countsP927);
error= (raw_counts-raw_countsP927);//
error_ratio=error/(double)raw_countsP927;

master_energy=0.1*ratio;
mut_energy=0.78125*1;
error_energy=mut_energy-master_energy;
percent_error=(error_energy/master_energy)*100;
 ///printf("- the rtc error measurement=s %d.\n", raw_distance);
///printf("MUT-TIME=%u,MASTER-TIME=%u,MASTER-PULSES PER MUT PULSE=%lf,TIME-DIFF=%lf,(MUT-MASTER/MASTER)=%lf\n",raw_counts,raw_countsP927,ratio,error,error_ratio);//((double)raw_counts/(double)raw_countsP927));//( *(pru0DataMemory_int+4)), (*(pru0DataMemory_int+5)));
//printf("MUT-TIME=%u,MASTER-TIME=%u,MASTER-PULSES PER MUT PULSE=%lf,(MASTER_PULSES-MUT_PULSES/MASTER-PULSES)=%lf\n",raw_counts,raw_countsP927,ratio,(ratio-1.00)/ratio);//
printf("\n%u,%u,%.3lf,%.3lf,%.3lf,%.3lf,%.3lf", raw_counts,raw_countsP927,ratio,master_energy,mut_energy,error_energy,percent_error);
/* Disable PRU and close memory mappings */
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
}
//int ii=0;

//int nos=0;
printf("\n");
minCounts27 = rawCounts27[0];
 minCounts30 = rawCounts30[0];
 maxCounts27 = rawCounts27[0];
 maxCounts30 = rawCounts30[0];
for (int  nos=0; nos < noofsamples; nos++){
    //count++;  - no need for it, you already have size!
    sumCounts27 += rawCounts27[nos];
 sumCounts30 += rawCounts30[nos];

    if ( maxCounts27 < rawCounts27[nos]){
        maxCounts27 = rawCounts27[nos];
    }
    if (minCounts27 > rawCounts27[nos]){
        minCounts27 = rawCounts27[nos];
    }

if ( maxCounts30 <rawCounts30[nos]){
        maxCounts30 = rawCounts30[nos];
}
if (minCounts30 > rawCounts30[nos]){
        minCounts30 = rawCounts30[nos];
    }

}
avgrawCounts27= sumCounts27 /float(noofsamples);
avgrawCounts30=sumCounts30 /float(noofsamples);
//MUT,MASTER
printf("\nmin30=%u avg30=%.3lf max30=%u min27=%u avg27=%.3lf max27=%u",minCounts30,avgrawCounts30,maxCounts30,minCounts27,avgrawCounts27,maxCounts27);

error= (avgrawCounts30-avgrawCounts27)/((float)sample);//raw_countsP927);//
error_ratio=error/(double)avgrawCounts27;//raw_countsP927;

master_energy=0.1*ratio;
mut_energy=0.78125*1;
error_energy=mut_energy-master_energy;
percent_error=((error_energy/master_energy)*100)/sample;

printf("\nAVG_PERCENT_ERROR=%.3f\n",percent_error);
memset(cmdLCD,'\0',100);
sprintf(cmdLCD,"PRINT_LCD_LINE_1 KWH-ERROR=%.3f",percent_error);
system(cmdLCD);


/*
for (int no=0; no < noofsamples; no++){
    //count++;  - no need for it, you already have size!
    sumCounts30 += rawCounts30[no];
    if ( maxCounts30 > rawCounts30[no]){
        maxCounts30 = rawCounts30[no];
    }
    if (minCounts30 < rawCounts30[no]){
        minCounts30 = rawCounts30[no];
    }
}
}
printf("\nmin27=%u avg27=%lf max=%u min30=%u avg30=%lf max30=%lf",minCounts27,
sumCounts27/noofsamples,maxCounts27,minCounts30,
sumCounts30/noofsamples,maxCounts30);
*/
   return EXIT_SUCCESS;
}
