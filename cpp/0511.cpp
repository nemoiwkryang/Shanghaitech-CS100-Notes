/*
lec 17 - rvalue ref and move

intro: s = a + b, for std::string class
    evaluate a + b -> temporary obj
    obj -> s
    dtor tempor obj

to make it faster, *steal* contents from the tmp obj

cmp - s = a
    not steal, 'cause std::string a should live long

diff: a lvalue, a+b rvalue
    no need to copy rvalue in class(just steal it)

more about lvalue, rvalue
    lvalue ref & ; rvalue ref && ;
    const & can also be bound to rvalues;
    && in param only matches rref, prior than rref -> &
    & in param matches both lref and rref


move op - std::move() change into rvalue; 
like ctor, copy, dtor, there is synthesized move op : use =default
    behavior - for each member, call move
so does =delete; but usually use lvalue & copy instead
    if =delete, copy of rvalue is banned 'cause overload and precedence


rule of five - copy ctor & assign op; move ctor & assign op; dtor
    move ctor / assign op not gen if any of the rest 4 are user-declard
        that is, never to be find move(&&), rvalue -> copy(&)
    copy ctor / assign op delete if any user-delared
        that is, deleted found, -> CE
    copy ctor / assign op generation is deprecated when class has a usr-delcred copy(any of the two) / dtor
        that is, generate but not recommended
    define 0 or 5 of them.

how to invoke a move op? std::move(), in <utility>
mean that telling the compiler that x will be moved from
    no more than promise that never use it later
    after move, cannot make any assumptions about the val
    for any complex type, use std::move in move op again
    e.g. T(T &&other) noexcept: str(std::move(other.str)) {}
var of type rvalue is an lvalue - call std::move for the members

concept:
    anything that has a name is an lvalue; exception - string literals are lvalues
    rref extend the lifetime of rvalue, e.g. 'a', func return val, expr
        which keeps the tmp obj like an lvalue
            usually you can replace all the declaration with rref declare and lvalue with std::move(lvalueName), but don't do that.
        rref means temporary obj

---

returning a temp - just instance = returnVal of (param -> expr of params)
    after cpp17 - no copy or move, just init, e.g. std::string s(a+b);
        called copy elision
*/

#include<iostream>
#include<string>
#include<utility>

class T{ // rvalue steal not useful here, 'cause no arr or smth used
// for better example see dynarray in HW5
// Due to SSO, steal std::string may not work for short strings
public:
    std::string a;
    int *num;

    T& operator =(const T& other){
        std::cout << "copied" << std::endl;
        if(this == &other) return *this;
        a = other.a;
        *num = *other.num;
        return *this;
    }
    T& operator =(T&& other)noexcept{
        std::cout << "moved" << std::endl;
        if(this == &other) return *this;
        delete num;
        a = std::move(other.a);
        num = other.num;
        other.num = nullptr;
        return *this;
    }
    T operator +(const T& other)const { // possible implementation of add op
        T tmp(*this);
        tmp.a += other.a;
        *tmp.num += *other.num;
        return tmp;
    }


    T(const T& other)
    :a(other.a), num(new int(*other.num))
    {
        std::cout << "copied" << std::endl;
    }
    T(T&& other)noexcept
    :a(std::move(other.a)),num(other.num)
    { // overload, matches rvalue ref, for move
        std::cout << "moved" << std::endl;
        other.num = nullptr;
    }
    T(const std::string &a_, const int &num_)
    :a(a_), num(new int(num_))
    {}
    T(){
        num = new int(0);
    }

    ~T(){
        delete num;
    }


    void printAttr()const{
        std::cout << a << " " << *num << ":" << static_cast<const void*>(a.data()) << " " << num << std::endl;
    }

};

int main()
{
    T a("aaaaaaaaaaaaaaaaaaaa",0);
    T b(a);
    T c, d;

    a.printAttr();
    b.printAttr();
    c = a;
    c = std::move(a);
    c.printAttr();
    d = c.operator+(b); // c + b -> rvalue -> steal
    d.printAttr();

    int n = 0;
    int &lrTolr = n;
    const int &lrTorr = 0; 
    int &&rrTorr = n+n;

    std :: cout << n << lrTolr << lrTorr << rrTorr << std::endl;
    return 0;
}