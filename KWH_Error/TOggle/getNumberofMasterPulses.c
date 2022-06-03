/* 
PRUSS program to drive a HC-SR04 sensor and display the sensor output in Linux userspace by sending an interrupt.
 The pruss program drives the HC-SR04 sensor and stores the output in memory. When the interrupt is sent, the Linux user space program can read it.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <pthread.h>
#include <unistd.h>
 
#define PRU_NUM 0
 
static void *pru0DataMemory;
static unsigned int *pru0DataMemory_int;
 
 // The child thread waits for the interrupt event 1 and executes the following code numerous times.
void *threadFunction(void *value){
   do {
      int notimes = prussdrv_pru_wait_event (PRU_EVTOUT_1);
      unsigned int raw_distance = *(pru0DataMemory_int+2);
//      float distin = ((float)raw_distance / (100 * 148));
  //    float distcm = ((float)raw_distance / (100 * 58));
      printf("thread counts=%u \r",raw_distance);// distin, distcm);
      prussdrv_pru_clear_event (PRU_EVTOUT_1, PRU0_ARM_INTERRUPT);
   } while (1);
}
 
int noofsamples,sampledelay;
int  main (int argc, char **argv)//void)
{
   if(getuid()!=0){
             printf ("must be executed with root privileges.\n");
      exit(EXIT_FAILURE);
   }

noofsamples=atoi(argv[1]);
sampledelay=atoi(argv[2]);
       // Create a child thread to handle interrupt requests
       // The interrupt it can handle (PRU_EVTOUT_1) is different from the interrupt used to notify the program that it is about to terminate (PRU_EVTOUT_0)
   pthread_t thread;
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
   prussdrv_init ();
       // The PRU_EVTOUT_1 interrupt is mainly to notify the Linux host program that the PRU program has stored the new measurement results in memory.
   prussdrv_open (PRU_EVTOUT_0);
   prussdrv_open (PRU_EVTOUT_1);
   prussdrv_pruintc_init(&pruss_intc_initdata);
//       / / Copy data to pru memory - another way
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory);
   pru0DataMemory_int = (unsigned int *) pru0DataMemory;
 
  //     / / Use the first 4 bytes as the sample number space
   *pru0DataMemory_int = noofsamples;//500;
    //   / / Use the second 4 bytes as the sampling delay (ms)
       *(pru0DataMemory_int+1) = sampledelay;//100; // The difference between samples is 2ms
 
   prussdrv_exec_program (PRU_NUM, "/root/KWH_Error/TOggle/getNumberofMasterPulses.bin");
   if(pthread_create(&thread, NULL, &threadFunction, NULL)){
               printf ("Create child thread failed!");
   }
 
       // The main thread should wait for interrupt event 0, then execute the following code once
   int n = prussdrv_pru_wait_event (PRU_EVTOUT_0);
       //Printf ("PRU program completed, event number: %d.\n", n);
       //Printf ("data in memory is: \n");
       //printf("-The number of samples used is %d.\n", *pru0DataMemory_int);
       //printf("-The delay used is %d.\n", *(pru0DataMemory_int+1));
   unsigned int raw_distance = *(pru0DataMemory_int+2);
//       Printf("-the last distance result is %d.\n", raw_distance);
printf("\nMUT Samples=%u,MUT Sample Delay=%u,Number of Master Pulses Received=%u\n", *pru0DataMemory_int, *(pru0DataMemory_int+1), raw_distance );
       // The original distance is in units of 10ns samples
       // distance in inches = time (ms) / 148 (according to the data sheet)
  // float distin = ((float)raw_distance / (100 * 148));
   //float distcm = ((float)raw_distance / (100 * 58));
   ///printf("-- A distance of %f inches (%f cm).\n", distin, distcm);
 
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}
