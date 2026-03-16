/*
introduction;
variables, arithmetic, expression, function, control flow;
scanf and printf;
env and compile

---

how to learn? try everything on slides

---

declaration - <type> name // static type
initialization
sizeof
double and float != real number

<Return Type> Name(<Params>){ // void if no param (required)
    //...
}

about void main() - no

scanf and printf
scanf ("%d") ignores any leading whitespace
and any whitespace char in format string skips all whitespaces until the next one
thus, "%d\n" will never end after the last input number

wrong format will cause undefined behavior
*/
#include<stdio.h>
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d%d",a,b);
    return 0;
}