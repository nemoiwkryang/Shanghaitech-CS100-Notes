/*
using pointer - call by address
pass var to a function - another independent var
pass address to a function - possible to change the original var

arrays - a sequence of N obj stored contiguously
Type arr_name[N]
call - arr_name[i]

- VLA - Type arr_name[Var] - not recommended
out of range is an undefined behavior that causes RE
initialization - global/static and local

type name[(N)]={1,2,3,...}(No more than N initializers)
init designated elements:
[]={[0]=1,2,3,[6]=7,8,...}
the elements not explicitly init is implicitly inited to zero

nested arrays - name[N_1][N_2]...
{{},{},...}, or just sequential {1,2,3,... or [][]=...}
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void fun(int *p){
    *p=2;
    return;
}

void swap (int *a, int *b){
    int t = *a;
    *a=*b;
    *b=t;
    return;
}

int main(void){
    int a=0,b=0;
    fun(&a);
    printf("%d\n",a);
    swap(&a,&b);
    printf("%d %d\n",a,b);
    int a[5][3]={0};
    return 0;
}