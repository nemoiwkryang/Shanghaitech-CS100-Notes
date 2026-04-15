/*
history of cpp
    c with classes, template, stl, ...

basic i/o - std::cin >> ; std::cout << ;
no need to format

cin - using reference
    returns cin - chained cin
    std::cin >> x >> y >> z; == (((std::cin >> x) >> y) >> z;
so does cout

no suffix ".h" for cpp header files

namespace std - avoid name collisions; all standard library names are here

e.g. void qsort(int a*, int n)  - write in another namespace

use "using namespace namespaceName;" to set a default namespace

use clibName instead of libName.h in #include - names introduced into std,and avoid awkward designs
*/

#include<iostream>

int main()
{
    std::cout << "Hello world\n";
    int a,b;
    std::cin >> a >> b;
    std::cout << "a + b = " << a << b << '\n';



    return 0;
}