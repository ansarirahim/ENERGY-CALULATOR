#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char cmd[100];
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "No arguments\n");
        return 1;
    }

    // Allocate memory for all the strings, plus one space per argument,
    // plus a NUL terminator.
    size_t size = 1;
//for (int i = 1; i < argc; i++) {
    for (int i = 3; i < argc; i++) {
        size += strlen(argv[i]) + 1;
    }
    char *str = (char *)malloc(size);
    if (!str) {
        fprintf(stderr, "No memory\n");
        return 2;
    }
int Line=atoi(argv[1]);
int Col=atoi(argv[2]);

    // Concatenate all arguments with a trailing space after each.
    // `size` keeps a running total of the length of the string being built.
    size = 0;
 for (int i = 3; i < argc; i++) {
    //for (int i = 1; i < argc; i++) {
        // sprintf() copies the argument to the buffer starting at the
        // offset specified as `size`.  There is also a space appended
        // (because it is specified by the format string) and a NUL
        // terminator (because that's what sprintf() does).
        size += sprintf(str + size, "%s ", argv[i]);

        // sprintf() returns the number of bytes written (excluding the
        // NUL that it added), which we use to keep track of the offset
        // of the NUL terminator.
        assert(str[size] == '\0');
    }
    // Remove trailing space.  The string is now terminated by two
    // consecutive NULs.  That's OK: only the first one matters.
    str[--size] = '\0';
/*
    printf("%s\n", str);
int len=0;
for(int len=0;len<100;len++)
{
if(str[len]=='\0')
break;
printf("\nstr[%d]=%c",len,str[len]);

}
printf("\n\nlength=%d\n",len);
*/
///////////////////////////////
//int Line=0;
//int Col=0;
for(int i=0;i<100;i++)
{
if(str[i]=='\0')
break;
memset(cmd,100,'\0');
if(str[i]==0x20)
{system("CHARACTER_SPACE_ON_LCD");
///printf("\ngot space\n");
}
else
sprintf(cmd,"PRINT_LCD %d %d %c",Line,Col,str[i]);
system(cmd);
Col+=7;
}
////////////////////////////////




    free(str);
}
