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
*/

#include<iostream>
#include<string>
#include<vector>

using ll = long long;

class T{
    static int cnt;
    int id;
    friend void printId(T&); // friend declaration, can be placed anywhere in the class def
public:
    using ll = long long;
    T():id(cnt++){}
    int T_id() const{
        return id;
    }
    friend class P;
};

class P{
public:
    static void access_T(T &t){
        t.id = t.id;
    }
};

void printId(T &t){
    std::cout << t.id << std::endl; // not work bc private without friend declaration
}

int T::cnt;

int main()
{
    ll n;
    T::ll m;
    T m1,m2,m3,m4;
    std::cout << m1.T_id() << m2.T_id() << m3.T_id() << m4.T_id() << std::endl;
    P::access_T(m1);
    return 0;
}