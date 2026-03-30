/*
pointer arithmetic- p+i points to the address i*sizeof(Type) after p, a[i] if array
same, i+/-p, p+/-=, ++/--p, p++/--, <, >
p=&a[0] <-> p=a if a Type[N]
pointer-pointer
passing array to function - 
*a is the same as a[]
usually, pass n with *a explicitly
subscript on pointers p[i]

when returning an array - pointer to global array / malloc

pointers to different types are of the different types

about nested arrays
T (*p)[N] pointer to array of T
T *p[N] array of pointer to T
how to pass- see example 1

cases that do not need an array

conert [][] to (*)[]

---

const variable and pointer
const T *p - add a lock to any variable/array (low level const-ness)
T *const p - never change the item pointed to (high level const-ness)

void * - can be converted to any
printf format - "%p"
c - static type, implicit conversion

dynamic memory - VLA, memory model - stack, heap, ...

malloc and free
void *malloc(size_t size);
void free(void *ptr) auto ignore null pointer
memory leaks
these objects goes beyond scopes

2d array - malloc n*m and then pointers is something similar to C array, or n* malloc m for easy implementation

void *calloc(size_t num, size_t each_size) - used for array, auto init to 0000
about malloc/calloc with size 0 - may not work but may alloc some - special judge required

unlimited lifetime, can catch OOM by checking null ptr

strings (c-style, char*)
char s[]="..."
scanf("%s",<char *>); not check overflow, not allowed in MSVC
gets(), the same, removed in C11;
better practice - fgets(<char *>,<length>,stdin)
max length count-1, ends when eol or eof

printf("%s",s);
puts(char *)
when print, search from s to any '\0'
\0 automaticlly added in "" to mark the end (remember to make the space for that)

manipulation, examination
strlen, strcpy, strcat, strcmp, strchr, ... see cppref
https://en.cppreference.com/w/c/string/byte.html
O(n), use at your own risk for complexity.

conversions with numeric - strtol, strtoll, ..., -s see cppref https://en.cppreference.com/w/c/string/byte.html

string literal (read-only, but not const in C), need copy for modification
the difference of *[] and [][] if init with str literal 
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void fun(int a[10]){
    printf("\n%zu\n",sizeof(a));
}

int main(void){
    int a[]={0,1,2,3,4,5,6,7,8,9};
    int *p=a;
    for(int i=0;i<10;i++){
        printf("%d",a[i]);
        printf("%d",p[i]);
        
        printf("%d",*(a+i));
    }
    for(;p<a+10;p++){
        printf("%d-",*p);
        printf("%lld ",p-a);
    }

    fun(a);

    // example 1
    int b[10][10][10]={0};
    int (*q)[10][10]=b;
    // int ***q=b;//err
    printf("%d\n",***b);
    int (*r)[10]=b[1];
    int (*s)=b[1][2];
    // int *r=b;

    int t=1;
    p=&t;
    printf("%p\n",(void *)p);

    int *pnew=(int *)malloc(sizeof(int)*8);
    for(int i=0;i<8;i++){
        pnew[i]=i;
    }
    for(int i=0;i<8;i++){
        printf("%d",pnew[i]);
    }
    free(pnew);

    // while(1){
    //     malloc(sizeof(int)*32);
    // }

    return 0;
}