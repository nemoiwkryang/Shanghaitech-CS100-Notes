/*
Inheritance and Polymorphism
*/

#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<numeric>

class Item{
    std::string m_name;
protected:
    double m_price = 0.0;
public:
    Item()=default;
    Item(const std::string &name, const double & price)
        : m_name(name),m_price(price){};
    const auto & Name()const{return m_name;}
    const auto Price(const int &cnt = 1)const{return m_price * cnt;}
};

/*
suppose we have a class item, we want to create a discounted item which is more than just an item
    - discount price, which is available above minimum discount quantity

"protected" members
    - private, but accessible in subclasses

use inheritance : "is-a" relationship
    - "is-a" is nothing but a link verb "is" and an article "a"
    - discounted item "is an" item
    - subclass of base class
    - subclass obj contains a subobj of base class
    - member(data and function except ctor, dtor) inherited
        - ctor of subclass need call ctor of parent class
        - dtor call dtor of parent class after destroying own members
        - sizeof(Derived_Class) >= sizeof(Base_Class)
    - never break the encapsulation of the base class
        - not directly init attributes in base class subobj in derived class obj

    - init order: base subobj -> other attributes
        - if not explicitly call base subobj init, default init
        - P.S. If user-declared ctor occurs, no default ctor synthesized

*/

class DiscItem : public Item{
    int m_minQuantity = 0;
    double m_discount = 1.0;
public:
    DiscItem(const std::string& name, const double &price, const int & minQ, const double & disc)
        : Item(name, price), m_minQuantity(minQ), m_discount(disc){}
    // cannot access private attr in Item
};

/*
Dynamic Binding: a derived class is a base class
    - D subclass of B
    - B* and B& can be assigned by D
*/

int main()
{
    DiscItem di("test",1, 5, 0.8);
    Item *I = &di;
    Item &I = di;
    // std::cout << i.Name() << ' ' << i.Price(2) << std::endl;

    return 0;
}
