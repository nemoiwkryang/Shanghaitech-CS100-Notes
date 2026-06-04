/*
lec 22 - more about inheritance and polymorphism 

example: a very abstract base class: shape
    we have Shape::draw and Shape::printInfo
    triangle, rectangle, circle has its own draw and printInfo

    the base class is too abstract that
        - all methods should be virtual
        - no behavior can be determined in methods in base class
        - should not instantiate base class

    introducing: pure virtual func

    virtual returnType funcName(params) qualifier = 0;
        cannot be called
    class with pure virtual func is an abstract class
        cannot be instantiated
    therefore, ptr / ref to an abstract class are only used for derived class
    
    without =0, which is a declaration w\o definition - error

    other practices
        - just return 0 (not recommended)
        - throw error (RE) (better)
    however, catch error in compile-time if possible

more about polymorphism
    - polymorphism: "once and for all"
        - single interface to different type entites
        - single symbol to represent multiple different types
    - methods
        - runtime - dynamic binding
            - calling a virtual func will look up all the derived classes
        - compile time - function overloading, templ, concept(cpp20)
            - form the class/function, and determine it in compile time

more about is-a inheritance
    - public inheritance: D is an obj of B; B is more general, obj_D can be used wherever obj_B exists
    
    > what about a penguin? a bird but cannot fly
        > try prevent the attempt from compiling

more about inheritance
    remember that impure virtual function is also inherited
    pure virtual ~ interface
    impure virtual ~ interface + implementation

    method - split interface(pure virtual) and default implementation(protected non-virtual)
        - e.g. virtual fly --> virtual fly=0, protected defaultFlys
            > therefore, every derived class must define a flys
            > or explicit call default fly in base class
    but the name "fly" is polluted: two different "fly"

    in short, pure virtual: interface only;
    impure virtual: interface + overridable default implementation
    non-virtual: interface + mandatory implementation

    > 一个例子：
        - impure virtual: 自动挡车都有油门，刹车，方向盘...
        - non-virtual: 某些标准规定了车有某些功能/部件
        - pure virtual: 自动挡和手动挡车开法区别很大
*/

#include<bits/stdc++.h>
using namespace std;
//我懒了

struct Shape{
    vector<pair<int,int>> nodes;
    virtual double area() const= 0;
    int size()const{
        return nodes.size();
    }
    Shape()=default;
    Shape(const vector<pair<int,int>> &nodes_)
        : nodes(nodes_){}
    virtual ~Shape() = default;
};

struct Triangle : public Shape{
    Triangle(const vector<pair<int,int>> &nodes_)
        : Shape(nodes_){}
    virtual double area() const override{
        auto& a = nodes[0];
        auto& b = nodes[1];
        auto& c = nodes[2];
        auto p = make_pair<int,int>(a.first-b.first,a.second-b.second);
        auto q = make_pair<int,int>(a.first-c.first,a.second-c.second);
        return fabs(p.first*q.second - p.second*q.first)/2.0;
    }
    ~Triangle() = default;
};

int main(){
    Triangle a({{0,0},{1,1},{1,0}});
    Shape &s = a;
    cout << s.area() << endl; 
    return 0;
}