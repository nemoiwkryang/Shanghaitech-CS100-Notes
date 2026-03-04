/*
variables and arithmetic types
C has static type system (python is dynamically-typed)
type known at compile-time
declare a variable - its scope

readability - declare right before used; meaningful names
*/
#include<stdio.h>
int x,y;//global
int main(void)
{
    int p,q;//local
    int max(int a,int b)
    {
        return a>b?a:b;
    }
    scanf("%d%d",&p,&q);
    printf("%d",max(p,q));
    return 0;
}