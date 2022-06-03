#include <stdio.h>
#include <iostream>
#include <sstream>
#include "SPIDevice.h"
#include "ASCII_TABLE5X7.h"
#include <cstdlib>
#include <cstring>>
        typedef unsigned char tByte;
using namespace std;
using namespace exploringBB;

char cmd[100];
int main(int argc, char **argv)
{
int Line=atoi(argv[1]);
int Col=atoi(argv[2]);
printf("\nargc=%d\n",argc);//
for(int k=3;k<argc;k++){
for(int i=0;i<100;i++)
{
if(argv[k][i]=='\0')
break;
memset(cmd,100,'\0');

///sprintf(cmd,"PRINT_LCD %d %d %c",Line,Col,argv[3][i]);
///printf(cmd);
///printf("\n");
//if(argv[k][i]==0x20)
//system("CHARACTER_SPACE_ON_LCD");
//else
{
sprintf(cmd,"PRINT_LCD %d %d %c",Line,Col,argv[k][i]);
system(cmd);
}
Col+=7;

}
system("CHARACTER_SPACE_ON_LCD");
}
return 0;
}
