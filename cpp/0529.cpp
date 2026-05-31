/*
Inheritance and Polymorphism
*/

#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<numeric>

class Item;
class DiscItem;

// class Item{
//     std::string m_name;
// protected:
//     double m_price = 0.0;
// public:
//     Item()=default;
//     Item(const std::string &name, const double & price)
//         : m_name(name),m_price(price){};
//     const auto & Name()const{return m_name;}
//     const auto Price(const int &cnt = 1)const{return m_price * cnt;}
// };

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

// class DiscItem : public Item{
//     int m_minQuantity = 0;
//     double m_discount = 1.0;
// public:
//     DiscItem(const std::string& name, const double &price, const int & minQ, const double & disc)
//         : Item(name, price), m_minQuantity(minQ), m_discount(disc){}
//     // cannot access private attr in Item
// };

/*
Dynamic Binding: a derived class is a base class
    - D subclass of B
    - B* and B& can be assigned by D
    - access D obj as if it is a B
        - but the obj is a D, therefore private members in B not accessible


static type and dynamic type of an expr
    - static type (compile time) - e.g. &Item
    - dynamic type (runtime) - e.g. actually reference to DiscountedItem, a derived class of the base class

may have same method name but difference implement
    - e.g. item and discounted_item :: Price
    - virtual functions
        - allow override so that function called is determined at runtime 
        - therefore, need no function overload to accept base class and derived ones
        - "virtual" necessary for function to be overridden, "virtual" and "override" optional for function overriding
    - virtual dtor
        - similar, used when using delete and other operations that need destroy
*/


class Item{
    std::string m_name;
protected:
    double m_price = 0.0;
public:
    Item()=default;
    Item(const std::string &name, const double & price)
        : m_name(name),m_price(price){};
    const auto & Name()const{return m_name;}
    virtual const double Price(const int &cnt = 1)const{return m_price * cnt;}
    virtual ~Item() = default;
};


class DiscItem : public Item{
    int m_minQuantity = 0;
    double m_discount = 1.0;
public:
    DiscItem(const std::string& name, const double &price, const int & minQ, const double & disc)
        : Item(name, price), m_minQuantity(minQ), m_discount(disc){}


    // cannot access private attr in Item
    virtual const double Price(const int &cnt = 1)const override{
        // with override, compiler checks override
        // changing param to int& will cause CE here
        return (cnt >= m_minQuantity)? cnt*m_discount*m_price : cnt*m_price;
    }


    virtual ~DiscItem()override = default;

    DiscItem(const DiscItem &);
    DiscItem& operator=(const DiscItem &);

};


void dynamic_binding_test(){
    DiscItem di("test",1, 5, 0.8);
    Item *pI = &di;
    Item &rI = di;
    std::cout << rI.Name() << ' ' << pI->Price(2) << std::endl;
}

/*
usage - smart ptr also support dynamic binding
    - implicit conversion from derived to base in unique_ptr, shared_ptr and smth else

---

about copy ctor - call the one in base first if manual
    - otherwise default init for any member not assigne

*/

DiscItem::DiscItem(const DiscItem& other)
    : Item(other), m_discount(other.m_discount), m_minQuantity(other.m_minQuantity){}
DiscItem& DiscItem::operator=(const DiscItem& other){
    Item::operator=(other);
    m_discount=other.m_discount;
    m_minQuantity=other.m_minQuantity;
    return *this;
}

/*
about synthesized copy ctor/assign
    - default for subobj first
    - then for derived class's own members
    - if no copy for base class or new members, the copy control functions will be deleted
*/

/*
about slicing - assign to non-ref-or-ptr types
    - because ctor of base class is called
    - therefore, no dynamic binding and function override

what about downcasting (ptr to base but actually to derived)
    - for polymorphic class
        - which has at least 1 virtual func (dtor/normal function)
        - derived from it are polymorphic
        > since have to inherit virtual, that dtor/normal func must be virtual 
    - use dynamic_cast<T>(expr)
        - only for ref and ptr
        - perform runtime type identification
            - if derived, succeed
            - if not, fail, return nullptr (for ptr) or throw exception std::bad_cast (for ref)
    - downcast is very slow
        - always use other cast if possible
        - e.g. static_cast, but cause UB if not derived
*/


int main()
{
    dynamic_binding_test();

    return 0;
}
