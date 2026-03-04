/*
the history of C
AT&T, K&R, UNIX
C89/ANSI, ISO C

reference to cppreference.com can be found in the titles

when compiling - save as .c, compile, run

function

<return type> <name>(<args>){ // if no args, use void
    <Body>
}

main function - 
int main(void, or something else){return 0;}

Output and return value
printf
scanf, input

"%d" indicates the input type (integer)
& get the address

about the scanf format - for %d, any white space will be skipped - others mentioned in recitations
about printf format

summary - header files, main function, scanf/printf, return value, string
*/
#include<stdio.h>

int f(int x){// a function, accept args and return
    return x*x;
}

double ff(double x, double y){
    return x+y;
}

int main(void){//main function, designated start of the program
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%s %d + %d = %d","Hello world\n",a,b,a+b);
    return 0;
}