/*
the history of C
AT&T, K&R, UNIX
C89/ANSI, ISO C

when compiling - save as .c, compile, run

function
*/
#include<stdio.h>

int f(int x){// a function, accept args and return
    return x*x;
}

int main(void){//main function, designated start of the program
    printf("%s","Hello world\n");
    return 0;
}