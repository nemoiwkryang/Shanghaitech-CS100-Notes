/*
better C - bool, true, false, function that should return bool
char literal '' are now char
implicit convertion that may introduce risk are errors
*/



#include<vector>
#include<iostream>
#include<string>
#include<cstdio> // to use stdio.h as if in C, name in namespaec std

int main(){
    // using namespace std;
    // using std::cin;
    // introduce cin, or smth into the scope
    // never write using in the main scope of a header file
    int x,y;
    std::cin >> x >> y; // calculated as (cin>>x -> cin)>>y;
    std::cout << x << y << std::endl; // endl outputs a \n, and refresh the buffer
    // a buffer stores the output and then outputs after full / other circumstances
    // flush output for every character output is time-consuming
    // if crashed without flush, all the characters stored in buffer just vanishes
    // manual flush - see cppreference


    //string - auto stop(by using iterator), auto mem, auto copy, auto init, auto cmp, auto concat
    std::string str; // empty
    std::cout << str << std::endl;

    str = "asdf";
    std::cout << str << std::endl;

    str = std::string(30,'3');
    std::cout << str << std::endl;

    std::string s2 = str;
    std::cout << s2 << std::endl; // copy

    std::cout << s2.size() << std::endl;

    s2 += s2; // better than s2 = s2 + s2 due to copy time
    std::cout << s2.size() << std::endl;
    
    s2 = s2 + "hello" + "world";//yes, s2 + "hello" -> std::string
    // s2 = "hello" + "world" + s2;//fail, const chat[] + const char[]
    std::cout << s2.size() << std::endl;

    std::cin >> s2;
    std::cout << s2.size() << std::endl; 
    // stop before whitespace, and the whitespace are left

    std::getline(std::cin, s2);
    std::cout << s2.size() << std::endl;
    // here, getline reads from the remaining whitespace and stops if \n \in whitespace
    // std::cin.ignore(), or customized methods like using getchar() and while
    // for more, see cppreference

    std::vector a(10,2); // vector is a class template, not type
    // vector<ElemType> is a type
    // auto copy, auto mem, auto init
    for(auto i : a){std :: cout << i << std :: endl;}

    a = {1,2,3};
    for(auto i : a){std :: cout << i << std :: endl;}

    a = std::vector<int>(10); // CTAD, Class Template Arg Deduction
    for(auto i : a){std :: cout << i << std :: endl;}

    a = std::vector(10,1);
    for(auto i : a){std :: cout << i << std :: endl;}

    a.clear();a.push_back(1);
    for(auto i : a){std :: cout << i << std :: endl;}
    
    a.front()++;a.push_back(1);a.back()++;
    for(auto i : a){std :: cout << i << std :: endl;}
    
    a.pop_back();
    for(auto i : a){std :: cout << i << std :: endl;}

    //v.at(i) as a substitude of v[i], but a lot slower
    // strategy of mem of vector - mem and time complexity
    // a. cannot hold - new for i+1 elems - x^2 time, 
    // b. cannot hold - new for 2i elems - log^2(x) but may cause memory problems
    // ...
    // use v.capacity() to get the current mem size

    // iterator and pointer method of for behaves differently if memory changes
    // be cautious if using range-for and push_back together
    return 0;
}