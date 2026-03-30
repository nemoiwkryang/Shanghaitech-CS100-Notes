/*
bitwise OP - ~, &, |, ^, <<, >>

preprocessor directives 预处理指令
#include, #define, ...
see when compile with --save-temp
#include = replace it with that file (copy - paste)
<filename> vs "filename"
#define = replace it with given text

be careful with these - define is NOT a function

pointer when init - local unstatic - wild pointer
    global/static - NULL

passing variables to be changed inside functions - use pointer (in cpp we have & for reference)
dereferencing a pointer to nothing - undefined behavior
usage of short-circuit evaluation - if (p != NULL && *p == ...)

array - array of the same type with different numbers of elements are different types

VLA(Variable Length Array) - not supported in this course, if have to, use calloc
buffer overflow and array out of range()
array init - [(N or the length of brackets if no number here)]={<0>,<1>,<2>,...(all 0)}, or {[<x>]=...,<x+1>, ...}
implicit init if global/static
multi-dimension, and init - see cppref, similar to 1d
sometimes convert to char to represent 1Byte

pointer subtraction - p1, p2 if point at elements in the same array -> ptrdiff_t (p.s. point to T[N] is allowed here)

well, actually, int[p]=p[int]
*/

#include<stdlib.h>
#include<stdio.h>

int main(void){
    int i[2]={2,3};
    int *p1 = &i[0],*p2=i;
    printf("%p\n%p\n%p\n",(void *)p1,(void *)p2,(void *)i);
    return 0;
}