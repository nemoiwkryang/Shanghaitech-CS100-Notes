/*
lec 25, 26 - template
*/

template <typename T>
int cmp(const T&a, const T&b){
    // const T& - T may not copyable, and const can accept rvalue
    if(a<b) return -1;
    if(b<a) return 1; // may not support '>'

    return 0;
}
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


int main()
{
    std::vector a{1,2,3,4};
    map(f<int>,a);
    for(auto &x: a)std::cout<<x <<" ";
    std::cout<<std::endl;
    print(1,2,3,4);

    return 0;
}