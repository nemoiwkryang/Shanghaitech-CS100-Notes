/*
lec 25, 26 - template
*/

// template <typename T>
// int cmp(const T&a, const T&b){
//     // const T& - T may not copyable, and const can accept rvalue
//     if(a<b) return -1;
//     if(b<a) return 1; // may not support '>'

//     return 0;
// }
/*
- function templ
    - guideline for compile to deduce and generate function (instantiation)
    - syntax:
    - Type parameter T
    - `typename` indicates T is a type
        - so does `class`
    - try minimize the requirements of arg types
        - e.g. < w/o >
        - e.g. copy / move

    ---

    - arg deduction: all arg must be known, but not necessarily specified
        e.g. 
        template<class A, class B>
        A func(B p){...}

        then:T1_obj = func<T1>(T2_obj) - calls <T1, T2>

    - pass by value cases:
        - ignore ref
        - ignore top-level const
        - decay arr
        - func decay to ptr to func
            - recall: ptr to func
                T(*Name)(params) = func
                usage: Name(params) or (*Name)(params)
    
        - same as auto p = a

    - forwarding reference / universal reference
        - param: T &&
        - rval - T:E - E&&
        - lval - T:E& - E& && - E&
            - ref collapsing
            - if & exists: &
            - otherwise: &&
        - ref always match the value
        - same as auto && 
    - used for perfect forwarding
        - value category unchanged
        - const not lost
        - remember that rref is lval
            - use std::forward<T>()
            - in <utility>
    
    ---

    - variadic templ
        > <typename ... Types>
        > void foo(Types ... params)
        - params function param pack
    
    - param pack
        - const / ref also available
        - expand to that many params
        - more about it - not discussed yet
    
        - auto, template, generic lambda

        - since cpp20: auto func param, which is template 

        
*/
#include<vector>
#include<iostream>
#include<utility>

template <class func, class vec>
void map(func f, vec &v){
    for(auto&i : v){
        i = f(i);
    }
}

template <class T>
T f(T t){
    return -t;
}

void print(){}

template <class First, class ... T>
void print(First f, T ... t){
    std::cout << f << " ";
    print(t...);
}

/*---*/

template<class P, class Q>
struct mypair{
    P first;
    Q second;
    mypair(P&& first_, Q&& second_)
        : first(std::forward<P>(first_)),second(std::forward<Q>(second_)){}
    mypair();

    template <class container>
    
    static mypair copy_from_seq(container C);
};

// mypair::mypair()=default; // arg list of class templ missing

template<class P, class Q>
mypair<P,Q>::mypair()=default;
// OK

mypair<int,int> a;
auto&& b = mypair<int,int>(1,2);


template<class P, class Q>
template<class container>
mypair<P,Q> mypair<P,Q>::copy_from_seq(container C){
    mypair<P,Q> t;
    t.first=C[0];
    t.second=C[1];
    return t;
} 


auto c = mypair<int,int>::copy_from_seq(std::vector({1,3}));
/*
class template
    - different types-instantiated classes are different types
    - inside def: param omitted when referring to self type
        - ctor, dtor, assign op, ...
    - outside def, member func: templ declare necessary
    - member func not intantiated if not used - delayed for saving resources
    - member func can also be templ
        - e.g. iterator
        - outside: two templ declarations necessary
*/


/*
- template alias - `using` declaration

- since cpp14: variable templates

- non-type params:
    - int, lval ref, ptr
    - (since cpp20) float, literal class
*/


/*
what if we want to compare char* and char*?
*/

#include<cstring>
template <typename T>
int cmp(const T&a, const T&b){
    // const T& - T may not copyable, and const can accept rvalue
    if(a<b) return -1;
    if(b<a) return 1; // may not support '>'

    return 0;
}
template <>
int cmp<const char*>(const char*const &lhs, const char*const &rhs){
    return std::strcmp(lhs,rhs);
}

int cmp(const char*const &lhs, const char*const &rhs){
    return std::strcmp(lhs,rhs);
}// this is function overload


/*
- specialization for function
    - <const char*> can be omitted
    - this is NOT overload
    - however, this example is not ideal, as string literals will not call this one
    - partial specialization not allowed
        - e.g. cannot specialize a function accepting class templates, such as typename and container<typename>

- "const ref" to ptr - high level constant: ...*const...
- function template recurrence: compile time recurrence
- operator: sizeof...(pack) - compile time
- if constexpr: compile time if
    - accepting a compile-time constant condition
    - if constexpr (condition) statement1 else statement2
    - e.g. used to prevent print() in our print function template, instead of overloading `print()`

*/

/*
application: curiously recurring template pattern (CRTP, 奇异递归模板模式, 一个类把自己作为模板参数传给自己的基类。)
- 1. to prevent copy/move, we can inherit from a uncopiable class
    - but ref/ptr of base class can refer to totally different classes
    - better implementation:
        - idea: 1. template accept incomplete type; 2. <Type1> and <Type2> 2 are different types
        - uncopyable template, and inherit Uncopyable<className>

- 2. increment
    - x++ is always defined: tmp; ++x; return tmp
    - using template: just inherit a incrementable class template
        - with tmp; ++x; return tmp
        - use static_cast to change Base* this to Derived* this
*/

/*
more about template metaprogramming
    - template is_same_type
        - partial specialize: <T,T> which gets a true
    - template is_ptr
        - also partial specialze: <T*>
    - more these: stl, <type_traits>

    ---

    - compute factorial in compile time
        - template class, static member = N * class<N-1>::member
    - check prime using recursion and template

    ---

    physics - use basic quantities to represent other quantities
        template <int mass, int length, int time, int charge,
        int temperature, int intensity, int amount_of_substance>
        struct quantity {};
        (NTTP; different params instantiate different types)
        using mass = quantity<1, 0, 0, 0, 0, 0, 0>;
        using force = quantity<1, 1, -2, 0, 0, 0, 0>;
        using pressure = quantity<1, -1, -2, 0, 0, 0, 0>;
        using acceleration = quantity<0, 1, -2, 0, 0, 0, 0, 0>;
*/
int main()
{
    std::vector a{1,2,3,4};
    map(f<int>,a);
    for(auto &x: a)std::cout<<x <<" ";
    std::cout<<std::endl;
    print(1,2,3,4);
    print(cmp(1,2),cmp("1","2"));
    return 0;
}