/*
C features in Cpp

better type
- bool, t/f, return type for bool and char
- string literals and char literals
- const init with literal are compile time const -> used for array length
- function () for 0 args (- ... for unknown numbers)

- type check
    - pointer check - ban implicit Type1 to Type2, except void
    - for explicit, use cpp_style cast
        - static_cast<T>(expr) those 'harmless' conversion
        - const_cast<T>(expr) remove const
        - reinterpret_cast<T>(expr) performs like c-style conversion  
    - better minimize casting

- type deduction and auto
    - type and compound types
    - int, double, char, ...
    - string literal -> const char*, decay performed
    - function return type after cpp14
    (- after cpp20, auto can be used as params, which can create function template)
    - usage - long type names (inside class, template, ...)
    - usage - lambda expr
        [empty, =(for copy) or &(for reference), or those variables that needed to pass](params){...}
    - decltype(expr) - deduce without evaluation
*/

#include<cstdio>
#include<iostream>
#include<vector>
#include<string>

void auto_deduce(){
    
    const int a=1;

    // int *pi=&a;
    // int *pi=(int*)&a;

    // float *qi=&a;
    // float *qi=(float*)&a;

    int b=1;
    int *p=&b;
    void *vp = p; 
    // char *cp = vp; 
    // char *cp = static_cast<char*>(vp); //for explicit cast, recommend using this in cpp

    // static_cast<Type>(expr) e.g. int, char, double; void* -> ElemType*
    // const_cast<Type>(expr) e.g. const T <-> T
    // reinterpret_cast<Type>(expr) e.g. void* - char*
    // dynamic_cast<Type>(expr) used in some Cpp features - discuss later in class

    auto arr={1,2,3}; // std::initializer_list
}

/*
functions in cpp
- default args
    - resolve by position, unlike Python
    - therefore, default values in the right

- function overloading
    - multi function with same name can be differenciated available
    - differenciated by params
    - basic rules for overload
        - exact match - identical types, decay, top-level const
        - low level const
        - intergral / floating-point promotion (bool/char-int, float-double)
        - other conversion(int-long, long-int, signed-unsigned)

- only overload op that do similar things

---

null pointer
    - NULL - likely to be int 0, defined by macro
    - nullptr

---
passing array as reference to array
better than function overloading - template, talk about it later
*/

// int fun(int x=0, int y){ 
int fun(int x, int y=0){ 
    return x+y;
}
double fun(double x, double y=0){ 
    return x+y+1;
}
std::string fun(std::string a, std::string b){
    return a+b;
}

void fun(int (&a)[10]){
    a[0]++;
}
void fun(int (&a)[]){
    a[0]++;
}
void fun(int *a){
    std::cout << "int*" << std::endl;
    *a++;
}

void fun(const int *a){
    std::cout << "const int*" << std::endl;
}

void function_overload(){
    int a[10]{};
    std::cout<< fun(1) << std::endl;
    std::cout<< fun('1') << std::endl; // - int
    std::cout<< fun(1.1f) << std::endl; // - double
    std::cout<< fun(2,3) << std::endl;
    std::cout<< fun(2.0,3.0) << std::endl;
    std::cout<< fun("2.0","3.0") << std::endl;
    fun(&a[0]); // int*

    // fun(a); // a[10] exact matchs (&a)[], (&a)[10] and *a
    // however, does not match (&a)[N] that N!=10
    for(auto i:a){
        std::cout << i << std::endl;
    }
}

int main()
{
    auto_deduce();
    function_overload();
    return 0;
}