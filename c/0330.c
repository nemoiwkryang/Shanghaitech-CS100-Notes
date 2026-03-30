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
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void fun(int a[10]){
    printf("\n%zu\n",sizeof(a));
}

int main(void){
    int a[10]={0,1,2,3,4,5,6,7,8,9};
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
    printf("%d",***b);
    int (*r)[10]=b[1];
    int (*s)=b[1][2];
    // int *r=b;


    return 0;
}