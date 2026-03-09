/*
bit, byte, sizeof()
n bits, 0-> 2^n-1 or -2^(n-1) -> 2^(n-1)-1
signed/unsigned short-int-long-long long
the width in this compiler:
2,4,8,8;
at least 2,2,4,8
that's an implementation-defined behaviors
usually int
format - %(h/l/ll)d/u

float - IEEE754
int_binary * 2^n
float, double, long double
usually double
format - %f, %lf, %Lf
4,8,16

(signed/unsigned) char
1Byte, ASCII

avoid unreadable numbers
e.g. 'n'-32 -> 'n'-('a'-'A')

escape sequence e.g. \', \\, \",
\t, \r, \n, ...
unicode not fully supported

boolean (since C99) - stdbool.h required in C
or, you can use 1 and 0

return a boolean expr without if/else

<type> name, delaration and initialization, global/local
*/
#include<stdio.h>
#include<stdbool.h>

int main(){
    char ch;
    double a,b;
    //scanf("%lf%lf",&a,&b);
    //printf("%lf",a+b);
    //printf("%lu%lu%lu%lu\n",sizeof(short),sizeof(int),sizeof(long),sizeof(long long));
    //printf("%lu%lu%lu\n",sizeof(float),sizeof(double),sizeof(long double));
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