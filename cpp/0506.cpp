/*
typedef ElemType Alias;
using Alias = ElemType;

can be used in classes
name is in the class scope
-> usage: ClassName::AliasName
or just try auto

many stl containerrs have some type alias2
e.g. string, vector, list, ... all have ::size_type
use the same name for consistency and generality.

---

class static members -> ~ global var
name is in the class scope
usage ClassName::VarName;
or InstanceName.VarName
shared by all class instances
application - assign a unique id

caution! additional defind required outside the declaration in the class

---

static member functions
name is in the class scope, usage ClassName::FuncName
no this, no changing non-static members

---

friend
friend functions
friend ReturnType FuncName (ParamType1, 2, ...); // Param Name not required

friend classes
friend class ClassName;

---

about function and class defination v.s. declaration

function - no body - declare; with body - defination

class def - declar of all members(var, func, ...)
member func can be def-ed outside
accessed by ClassName::MemberName

class declar : class / struct Name;
declares an incomplete type, cannot create an object, cannot access members
declare a ptr / ref to it OK;

---

more about destructors
    called when end of scope / delete / termination of program
    every class need a destructor
    empty dtor == default, which destroy every member
    automaticly call member destructors if class
    when dtor function is called, members are still accessible in the function
    dtor order == reverse of declare in class def order
*/

#include<iostream>
#include<string>
#include<vector>

using ll = long long;

class T;

class P;

void printId(T &t); // declaration; ref to incompl type OK


class T{
    static int cnt;
    int id;
    friend void printId(T&); // friend declaration, can be placed anywhere in the class def
    std::string name;
public:
    using ll = long long;

    T(const std::string name = "No Name"):id(cnt++), name(name){}

    int T_id() const;

    friend class P;

    ~T(){
        std :: cout << "Destruct: " << id << " " << name << std :: endl;
    } // OK; No new / *alloc used 
    // ~T(){}, or ~T(){/* Print the members */} Also OK
};



class P{
public:
    static void access_T(T &t){
        t.id = t.id;
    }
};
int T::cnt = 0;

int main()
{
    ll n;
    T::ll m;
    T m1("0"),m2("1"),m3("2"),m4;
    std::cout << m1.T_id() << m2.T_id() << m3.T_id() << m4.T_id() << std::endl;
    P::access_T(m1);
    return 0;
}

void printId(T &t){ // defination
    std::cout << t.id << std::endl; // not work bc private without friend declaration
}

int T::T_id() const{
    return this->id;
}