//caution! undefined behavior may not be warned

/*
call a function - <name>(<params>)
() here - function call operator
about return value - void -> no return value; others with no return value - undefined return value。
about scopes, declare and define - more will be discussed later
declare multiple times, but define once
scope - global - functions - blocks in functions - blocks in blocks - ...
best practice - scope and name loopup - declare right before usage

global variables and static variables
static and global variables will be initialized automatically
const
(-O2 automatically initialize local variables)

pointers : *, pointer, &
&var --return--> type *
*expr -> that variable (not an immutable value)

NULL, or 0, but in C23/C++11, there is a better practice nullptr
about implicit init of pointers - same as variables, uninit-ed pointers are called wild pointers

de-reference-able = not causing undefined behave = points to existing obj
(dereference = the inverse operation of reference (&), that is *)


*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
double divide(int a,int b){
    static bool used_flag=false; //the second time, the assignment will be bypassed
    if (used_flag){
        printf("used\n");
    }
    used_flag=true;
    if (b==0){
        exit(EXIT_FAILURE);
    }
    return 1.0*a/b;
}
int main(){
    int x,y;
    scanf("%d%d",&x,&y);
    double res=divide(x,y);
    printf("%lf\n",res);
    res=divide(x,y);

    int i=42;
    int *p = &i;
    printf("%d\n",*p);
    (*p)++;
    printf("%d\n",*p);
    
    return 0;
}