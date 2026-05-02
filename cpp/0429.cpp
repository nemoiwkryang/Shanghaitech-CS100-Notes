/*
about class

simple class - struct with functions
access like struct - member, method

public and private - specifies until the next access specifier or end
    - default - private for class, public for struct

pointer "this" 
    void getname(const std::string &newName){
        name = newName;
    }
is actually 
    void getname(Stu *this,const std::string &newName){
        this->name = newName;
    }

about const member functions
    - syntax - name(param) const{...}
    - guarantees read only
        - in the function, or calling other member functions
        - in const functions, *this is a const object
        - so does the members

class constructors - how to init an obj
    often overloaded for multiple ways of init


    to init the attributes with expressions:
    ```
    className(p1, p2, ...)
        [: attr1(expr1), attr(expr2), ... ]{ // [] is for optional
        ...
        ... // e.g. validate the attributes;
        // for the registry.h in tank, reg can be here
    }
    ```
    special function - no return value
    compare - __new__ and __init__ in python class
    init order - declaration, not initialization
    in-class init
        {} or =, but not ()
    default-init 

    (actually, : some var in initializer list can be rewrite in the function part
        using this, we first default-init, and then assign - just like a usual function)
    cannot be default-initialized:
        reference not default, not assign
        builtin const type cannot be default
        const cannot be assigned

more about default constructor
    no user-declared -> synthesize a default
        - if any in-class init, ok
        - if not written init behavior, default-initialize
        - if cannot default-initialize - give up it -> CE if try default init
    user-declared occurs -> use function = default if want to synthesize one

exceptions - 
static are not discussed here
mutable members can be modified with const member functions
*/

#include<iostream>
#include<vector>
#include<string>

class Stu{ // howerver, for a real student, there may be no default student -> do not leave a default constructor
private:
    std::string name{"Test Name"};
    std::string id{"2000000000"};
    const int entranceYear{2000};
    const int &test;
    // const int entranceYear; fail

public:
    // void setAttribute(const std::string &newName, const std::string &newId, const int &newYear){
    //     this->name = newName;
    //     this->id = newId;
    //     this->entranceYear = newYear;
    // }
    Stu(const std::string &name_, const std::string &id_, const int &entranceYear_)
        : name(name_), id(id_), entranceYear(entranceYear_), test(entranceYear){
            printName();
    }
    
    Stu(const std::string &name_, const long long &id_, const int &entranceYear_)
        : name(name_), id(std::to_string(id_)), entranceYear(entranceYear_), test(entranceYear){
            printName();
    }
    Stu() = default; // because of reference failure, no default synthesized

    void printName() const{
        // this->name="0"; // fail 
        std::cout << name << " " << id << " " << entranceYear << std::endl;
    }
    bool valid() const{
        return std::stoi(id.substr(0,4)) == entranceYear; 
    }
};

int main()
{
    Stu s_str("Harikae","2025123456",2025);
    Stu s_inte("Harikae",2025123456,2025);
    // Stu s_empty; // failed, int& Stu::test’ should be initialized, so default constructor cannot be synthesized -> deleted function
    Stu s_try_empty(); // No, the empty () will be parsed as declar function

    // better than s.setAttribute("Harikae","2025123456",2025);
    s_inte.printName();
    std::cout << std::boolalpha << s_inte.valid() << std::endl; 
    return 0;
}