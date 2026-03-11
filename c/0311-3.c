/*
last time - arithmetic types

operators and control flow
+, -, *, /
unary and binary op
precedence - unary +/- > *, /, % > binary +/-
type conversions occurs before evaluation of expressions
e.g. double op integer -> double op double
integer overflow -> undefined behavior

%: (a/b)*b+(a%b) == a
compuond assignment op +=， -=，...
increment/decrement op ++, --

if-else

if(<condition>) <statement> else <statement>

use formatter

while (<condition>) statement
something tricky - while(--n)
break, and continue
*/
#include<stdio.h>
int main()
{
    // double a,b;
    // char ch;
    // if (scanf("%lf %c %lf",&a,&ch,&b)!=3){

    //     printf("ERR");
    //     return -1;
    // }
    // double ans;
    // if (ch == '+')ans=a+b;
    // else if (ch == '-')ans=a-b;
    // else if (ch == '*')ans=a*b;
    // else if (ch == '/')ans=a/b;
    // else {
    //     printf("ERR");
    //     return -1;
    // }
    // printf("%lf\n",ans);
    int a=1e9;
    long long b=a*a;
    printf("%lld\n",b);
    b=b*b;
    printf("%lld\n",b);
    b=b*b;
    printf("%lld\n",b);
    return 0;
}