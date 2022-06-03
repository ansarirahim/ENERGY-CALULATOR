#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <pthread.h>
#include <unistd.h>

//#define EXE1 "/root/160718/512/P9_27/P927kwh"
//#define EXE2 "/root/160718/512/P9_30/P930kwh"
#define EXE1 "/root/160718/512/P9_27/tp"
#define EXE2 "/root/160718/512/P9_30/tp"

int main()
{
//printf("\n");
system(EXE1);
//printf("\r,");
system(EXE2);
printf("\n");
}
