/*
last time - arithmetic types

operators and control flow
+, -, *, /
unary and binary op
*/
#include<stdio.h>
int main()
{
    double a,b;
    char ch;
    if (scanf("%lf %c %lf",&a,&ch,&b)!=3){

        printf("ERR");
        return -1;
    }
    double ans;
    if (ch == '+')ans=a+b;
    else if (ch == '-')ans=a-b;
    else if (ch == '*')ans=a*b;
    else if (ch == '/')ans=a/b;
    else {
        printf("ERR");
        return -1;
    }
    printf("%lf\n",ans);
    return 0;
}