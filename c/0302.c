/*
now I'm trying gcc -x objective-c to compile a c code
 gcc -x objective-c -std=c17  `gnustep-config --objc-flags` -lgnustep-base <.m file> -o <output>

0302-lec0
syllabus, contents, course...

if LLM, why learn programming?

learn how to interact with computers

learn with, but not abuse LLM

a bridge between language and your machine, machine code <-> assembly code <--compile/interpret-- high-level languages

a tool - compiler explorer
compilers
about cpp and "c with classes"
base on c17 and c++17
standard, see it at cppreference

objectives-learn c/c++ - solve problem using code, write in C/cpp with the correct syntax, know basic ideas of programming

course structure - lec and recitation

72% hw 
OJ, form of IOIs
22% mid
4% quiz (without announce)
2% recitation attendance check

check piazza - once per 12hrs 

suggested reference books
*/
#include<stdio.h>
int main()
{
    int a;
    if (scanf("%d",&a)==1);
    else{return -1;}
    printf("%d\n",a);
    return 0;
}