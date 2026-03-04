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
//global
int out;
void print(void){
    printf("%d\n",out);
}
int main(void)
{
    int p,q;//local
    int max(int a,int b)
    {
        return a>b?a:b;
    }
    int x,y;
    scanf("%d%d",&p,&q);
    out=max(p,q);
    print();
    printf("%d %d\n",x,y);//uninitialized value printed
    return 0;
}