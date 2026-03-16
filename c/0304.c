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
/*
variables and arithmetic types
C has static type system (python is dynamically-typed)
type known at compile-time
declare a variable - its scope

readability - declare right before used; meaningful names
everytime initialize a variable when declared

some basic arithmetic types
from binary, bit, byte to types

*/
#include<stdio.h>

int f(int x){// a function, accept args and return
    return x*x;
}

int out;
void print(void){
    printf("%d\n",out);
}
double ff(double x, double y){
    return x+y;
}
int max(int a,int b)
{
    return a>b?a:b;
}
int main(void){//main function, designated start of the program
    int a,b;
    int p,q;//local
    int x,y;
    scanf("%d%d",&p,&q);
    out=max(p,q);
    print();
    printf("%d %d\n",x,y);//uninitialized value printed
    scanf("%d %d",&a,&b);
    printf("%s %d + %d = %d","Hello world\n",a,b,a+b);
    return 0;
}