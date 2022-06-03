// PRUSS program to drive a RTC Signal Error measurement and store the output in memory
// that can be read by a Linux userspace program when an interrupt is sent
// Writen by A. R. Anasri

.origin 0               // offset of start of program in PRU memory
.entrypoint START       // program entry point used by the debugger

#define TRIGGER_PULSE_US    10
#define INS_PER_US          200
#define INS_PER_LOOP        2
#define TRIGGER_COUNT       (TRIGGER_PULSE_US * INS_PER_US) / INS_PER_LOOP
#define SAMPLE_DELAY_1MS    (1000 * INS_PER_US) / INS_PER_LOOP
#define PRU0_R31_VEC_VALID  32
#define PRU_EVTOUT_0	    3
#define PRU_EVTOUT_1	    4

// Using register 0 for all temporary storage (reused multiple times)
START:
   // Read number of samples to read and inter-sample delay
   MOV    r0, 0x00000000        //load the memory location, number of samples
   LBBO   r1, r0, 0, 4          //load the value into memory - keep r1
   // Read the sample delay
   MOV    r0, 0x00000004        //the sample delay is in the second 32-bits
   LBBO   r2, r0, 0, 4          //the sample delay is stored in r2
///////////////////////////////////////////start
mov r3,0;
mov r4,0;//for p9.27
//
 mov r0,70
//512
///////////// mov r0,10
//WBC    r31.t3
 //wbs  r31.t14
WBS r31.t2
WBC r31.t2
LOOPFORONECYCLE:
//SUB r1,r1,1	///
SUB r0,r0,1
   // start counting (measuring echo pulse width)  until the echo goes low
COUNTING:
   wbs  r31.t14
   wbc r31.t14
   ADD    r3, r3, 1             // increment the counter by 1
   QBBC   COUNTING, r31.t2      // loop if the echo is still high
COUNTINGLOW:
   // at this point the echo is now low - write the value to shared memory
        wbs r31.t14
        wbc r31.t14
        ADD R3,R3,1
        QBBS COUNTINGLOW,r31.t2
////////////////////////////////////////////////enditeration2
//STARTING p9.27
mov r4,0;
// mov r0,512
 //mov r0,1
WBS r31.t5
WBC r31.t5
COUNTING27:
   wbs  r31.t14
   wbc r31.t14
   ADD    r4, r4, 1             // increment the counter by 1
   QBBC   COUNTING27, r31.t5      // loop if the echo is still high p927
//
COUNTINGLOW27:
   // at this point the echo is now low - write the value to shared memory
        wbs r31.t14
        wbc r31.t14
        ADD R4,R4,1
        QBBS COUNTINGLOW27,r31.t5

//end p9.27


///WBC r31.t2
QBNE LOOPFORONECYCLE, r0,0	//R1,0		//r0,0
MOV    r0, 0x00000008        // going to write the result to this address
   SBBO   r3, r0, 0, 4          // store the count at this address
///////write /for p9.27
MOV    r0, 0x0000000C
 SBBO   r4, r0, 0, 4
///end 

//////////////////////////////////////////end
   // generate an interrupt to update the display on the host computer
   MOV R31.b0, PRU0_R31_VEC_VALID | PRU_EVTOUT_1
//   QBNE   MAINLOOP, r1, 0       // loop if the no of iterations has not passed

END:
   MOV R31.b0, PRU0_R31_VEC_VALID | PRU_EVTOUT_0
   HALT
