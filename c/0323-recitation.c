/*
Literal v.s. Variable, Operator, Control Flow
Literal, Variable, Rvalue, Lvalue
int, if no suffix, e.g. (u)(l/ll); and some 0x 0b 0o; no negative literal int
double, if no suffix, e.g. (u)(f/l); and some like 1e8
char = 1Byte int

* and / calculates from left to right so 1.0*a/b
however, the time functions called in an exp is not specified
some functions for char in ctype.h e.g. digit, lower, upper, ...
therefore, i=i++ + 2 is an undefined behavior

only && || ?: and , specify the order of evaluation / call
&& || left to right
<condition>?<a>:<b> condition first

op on each bit - ~, &, |, ^, <<, >>
some tricks using bit ops

why do-while and switch-case not popular - scope problems

about how to debug - breakpoint, continue, step by step, step in/out (a funciton)
*/
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int calc(int x){
    int y;
    y=x;
    return x*x;
}

int main(void){
    int a=0;
    while(1){
        scanf("%d",&a);
        a=calc(a);
        printf("%d\n",a);
    }
    return 0;
}