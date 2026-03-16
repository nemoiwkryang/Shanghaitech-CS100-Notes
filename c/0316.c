/*
while and for
for (init (assignment/declaration); condition; iteration_expr)
(equivalent to ) init; while(condition){interation}
variables declared inside only have the scope of the loops

op precedence and evaluation order
e.g. ++i + i++, i++ + 1, ..., are undefined behavior
see operator as function (e.g. i++ vs ++i)
comparison ops, logical ops, ...
"!" > cmp op > && > ||, ...
short - circuit evaluation - a && b - a==0 -> stop; a || b - a==1 -> stop;
?: 
assignment operator "="

do-while
switch，case, default # case label must be an integer constant expression

function
*/
#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);

    for (int i=0;i<n;i++){}
    while (n--){}
    return 0;
}