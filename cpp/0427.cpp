/*
history of cpp
    c with classes, template, stl, ...

<iostream>
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

---

stl - string
cin, cout, .size()
ignore prefix and suffix whitespace
assign - (num, chr), (str),{str}, "str"; 
str concat - +, +=
available with char * but at least one operand be cpp string; left associated
the behavior of + and +=
    + creates a temporary object, while += just modifies lhs
lexicographical cmp of str - just use the compare ops

mind the op precedence

for loop - range based
*/

#include<iostream>
#include<string>
int main()
{
    std::cout << "Hello world\n";
    int a,b;
    std::cin >> a >> b;
    std::cout << "a + b = " << a << b << '\n';

    std::string str(3,'n');
    std::cout << str << std::endl; 

    std::cin >> str;

    std::cout << str.size() << " " << str.empty() << " " << str << " " << str+"asdf" << std::endl;

    // str = "hello" + "world" + str; // fail 
    std::cout << std::boolalpha << (std::string("Hello") < std::string("Hellp")) << std::endl;


    for(auto c : str){
        std::cout << c << std::endl;
    }
    return 0;
}