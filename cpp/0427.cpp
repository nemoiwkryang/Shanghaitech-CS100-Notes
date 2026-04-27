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
cin, cout, .size(), .empty()
ignore prefix and suffix whitespace

std::getline() may fail due to  \r\n problems

assign - (num, chr), (str),{str}, "str"; 
auto init

str concat - +, +=
available with char * but at least one operand be cpp string; left associated
the behavior of + and +=
    + creates a temporary object, while += just modifies lhs
lexicographical cmp of str - just use the compare ops

mind the op precedence

for loop - range based

for (Elemtype var : obj)

convert string and numbers
    stol,stoi,..., to_string

---

reference & (not that used in dereference and get-address)
declare a reference - Elemtype &Name = Var; rhs necessary, or CE

the type of a reference is "Elemtype &"
creates an alias; can't be re-bind
should be bound to existing objects (lvalues)
    there are no reference/pointer to reference
applies to only one identifier

using reference in range-for, we achieve similar effects like C-style for loop
by using reference (or pointer), we avoid copy when passing argument
but, mind those objects that cannot be bound to
introducing - reference to const - can be bound to anything

---
*/

/*
vector - in stl file <vector>
class template, need to pass a value type
std::vector<ElemType> name;
type - std::vector<ElemType>
init - name{} or name = {} , or (num[, init_value]) for batch init 
copy - just use assignment =
feature after Cpp17 - class template arg deduction - auto deduce value type 

std::vector.size(),.empty()
std::vector.clear(), push_back(), pop_back()
.back() -> return &Elemtype = last value 
same as .front()
vector[i] - may cause UB

the style of STL - integrate better things without more problems
    basic op automatical
    auto init
    auto copy
*/


#include<iostream>
#include<string>
#include<vector>

void customswap(int&, int&);
void string_and_reference(){
    
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

    std::string s = std::to_string(123.4567);
    int i = std::stoi(s);
    std::cout << s << " " << i << std::endl;

    std::cout << std::string(10,'-') << std::endl;

    // -------------------------------

    a=1,b=2;
    customswap(a,b);
    std::cout << a << " " << b << std::endl;

    // int &r = 1 + 2; // fail
    // int &r = 1; // fail
    // int &r = a + b; // fail

    int &alias = a;

    int *p=&a;

    int *q=&alias;

    int *&palias = q; // ref to pointer

    // int &*qalias = q;  pointer to ref 

    std::cout << *p << ' ' << *q << std::endl;


    std::string num_str=std::to_string(12345);
    for(char &c : num_str){
        c+=1;
    }
    std::cout << num_str << std::endl;
}
void vectors(){
    std::vector a(3,2);
    std::cout << a.size() << '\n';

    a.front()++;
    std::cout << a.front() << '\n';
    
    a.push_back(1);
    std::cout << a.size() << '\n';

    a.pop_back();
    std::cout << a.size() << '\n';

    for(int x : a){
        std::cout << x << '\n';
    }

    std::cout << a[0] << '\n';

    a.clear();
    std::cout << a.size() << '\n';

}
int main()
{
    string_and_reference();
    vectors();
    return 0;
}
void customswap(int &a, int &b){
    int t=b;
    b=a;
    a=t;
}