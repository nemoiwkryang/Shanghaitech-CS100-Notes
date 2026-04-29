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
*/

// int fun(int x=0, int y){ 
int fun(int x, int y=0){ 
    return x+y;
}
double fun(double x, double y=0){ 
    return x+y;
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
    *a++;
}

int main()
{
    auto_deduce();
    std::cout<< fun(1) << std::endl;
    std::cout<< fun(2,3) << std::endl;
    std::cout<< fun(2.0,3.0) << std::endl;
    std::cout<< fun("2.0","3.0") << std::endl;
    int a[10]{};
    fun(&a[0]);
    // fun(a); // a[10] exact matchs (&a)[], (&a)[10] and *a
    // however, does not match (&a)[N] that N!=10
    for(auto i:a){
        std::cout << i << std::endl;
    }
    return 0;
}