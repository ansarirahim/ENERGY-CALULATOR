// PRUSS program to drive a HC-SR04 sensor and store the output in memory
// that can be read by a Linux userspace program when an interrupt is sent
 // The pruss program drives the HC-SR04 sensor and stores the output in memory. When the interrupt is sent, the Linux user space program can read it.
//////////This will count till the number of pulse low levels 
 
.origin 0              
.entrypoint START      
 
#define TRIGGER_PULSE_US    10
#define INS_PER_US          200
#define INS_PER_LOOP        2
#define TRIGGER_COUNT       (TRIGGER_PULSE_US * INS_PER_US) / INS_PER_LOOP
#define SAMPLE_DELAY_1MS    (1000 * INS_PER_US) / INS_PER_LOOP
#define PRU0_R31_VEC_VALID  32
#define PRU_EVTOUT_0	    3
#define PRU_EVTOUT_1	    4
 
 // use r0 for all temporary storage (reuse multiple times), r1 stores the number of samples, r2 stores the trig pulse width, r3 stores the echo pulse width
START:
       MOV r0, 0x00000000 // sample storage address
       LBBO r1, r0, 0, 4 // Load to r1
       MOV r0, 0x00000004 // Sampling delay
       LBBO r2, r0, 0, 4 // load to r2
 
MAINLOOP:
       MOV r0, TRIGGER_COUNT // store the trigger pulse width
       SET r30.t5 // set
 
TRIGGERING:                     
       SUB r0, r0, 1 // delay 10us
       QBNE TRIGGERING, r0, 0 // loop until the end of the trigger pulse delay
       CLR r30.t5 // The delay ends and the triger is set to zero. At this point, the Trig pulse has been sent out.
 
       MOV r3, 0 // clear counter r3, will store the pulse width of echo
       WBS r31.t2	///3 // Wait for echo to go high
 
COUNTING:
       ADD r3, r3, 1 // start counting (measuring echo pulse width) r3 += 1
       QBBS COUNTING, r31.t2	//3 // loop until echo goes low
 
       MOV r0, 0x00000008 // The echo is low now - write the value to shared memory
       SBBO r3, r0, 0, 4 // first stored in r0
 
//////////////////////////////////////////////////////////////////////////////////////
       SUB r1, r1, 1 // another sample iteration, so subtract 1 from the number of iterations
       MOV r0, r2 // delay between iterations
SAMPLEDELAY:			
       SUB r0, r0, 1 // Do this loop r2 times (1 millisecond each time)
       MOV r4, SAMPLE_DELAY_1MS // Load 1ms delay to r4
DELAY1MS:
   SUB	  r4, r4, 1             
       QBNE DELAY1MS, r4, 0 // loop until the end of 1ms
       QBNE SAMPLEDELAY, r0, 0 // Repeat the loop until the end of the delay
////////////////////////////////////////////////////////////////////////////////////// 
 
   MOV R31.b0, PRU0_R31_VEC_VALID | PRU_EVTOUT_1 // Generate an interrupt to update the display on the host
       QBNE MAINLOOP, r1, 0 // continue to loop if the number of iterations is not 0
 
END:
   MOV R31.b0, PRU0_R31_VEC_VALID | PRU_EVTOUT_0
   HALT
