/*
OP overload - provide customized behaviors of op for class types, e.g. =, <<, >>, +, cmp ops, [], *, ->

for member func
    unary -> instance.op
    binary -> instance.op(param)
    multiple -> instance.op(...)

for non-member func
    op(param1, param2, ...)

at least 1 of the operand should be class
new op not allowed; not changing associativitiy, precedence and evaluation order

if binary op  +, -, ..., no auto convert for lhs operand, e.g. 0+r -> 0.operand+(r) -> error

for floating-point precision errors, use int for compare instead

operators should be unambigous for users - use named functions for more information

++ and -- behavior
    ++x -> x.op++(); x++ -> x.op++(0)

IO op >> and << 

for dynarray[i], as if .op[i](i), so return ptr[i]; -> &pointeeType

for *autoptr, as if .op*(), so:
    T &op*() const{return ptr_to_shared_ptr->...}
    adding const, this -> const T*, and ptr_to_shared_ptr is T *const, not const T*
    high level const means that you can modify that obj returned 

---

usr-def type conv 
implicit, explicit
what_cast<U>(expr), or U(expr)
arithmetic conv are often allowed implicit
type conv in class
A. ctor with exactly 1 param of type T, which converts T to ClassName
B. type conversion OP - operator TypeName() ...

to disallow implicit ctor as conv, write explicit

contextual conv to bool - 
    expr -> X, X explicit conv op bool() -> bool
    implicit applicable in: if, while, for, do-while, !, &&, ||, ?:
    e.g. unique_ptr and shared_ptr can be just used in conditions
*/

#include<algorithm>
#include<string>
#include<iostream>
#include<vector>
#include<numeric>

class rational{
    int m_num;
    unsigned m_denum;
    void simplify(){
        int  gcd = std::gcd(m_num, m_denum);
        m_num/=gcd;
        m_denum/=gcd;
    }

    friend rational operator-(const rational&);
    friend rational operator+(const rational&, const rational&);
    friend rational operator-(const rational&, const rational&);
    friend rational operator*(const rational&, const rational&);
    friend rational operator/(const rational&, const rational&);
    friend bool operator<(const rational&, const rational&);
    friend bool operator>(const rational&, const rational&);
    friend bool operator==(const rational&, const rational&);
    friend bool operator<=(const rational&, const rational&);
    friend bool operator>=(const rational&, const rational&);
    friend bool operator!=(const rational&, const rational&);
    friend std::istream &operator>>(std::istream &, rational &);
    friend std::ostream &operator<<(std::ostream &, const rational &);

    public:

    explicit rational(int num = 0, unsigned denum = 1):m_num(num), m_denum(denum){}

    double to_double()const{return static_cast<double>(m_num)/m_denum;}


    rational& operator += (const rational &other){
        m_num = m_num*static_cast<int>(other.m_denum) + other.m_num*static_cast<int>(m_denum);
        m_denum *= other.m_denum;
        simplify();
        return *this;
    }

    rational& operator -= (const rational &other){
        return *this += -other;
    }

    rational & operator++(){
        m_num+=static_cast<int>(m_denum);
        simplify();
        return *this;
    }
    rational operator++(int){
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    // similar to to_double
    operator double() const {return double(m_num)/m_denum;}

};

std::istream &operator>>(std::istream &is, rational &R){
    int x,y;
    is >> x >> y;
    if(!is){
        x = 0;
        y = 1;
    }
    if(y < 0){y=-y, x=-x;}
    R = rational{x,static_cast<unsigned int>(y)};
    return is;
}
std::ostream &operator<<(std::ostream &os, const rational & R){
    return os<<R.m_num << '/' << R.m_denum;
}
rational operator-(const rational&x){
    return rational(-x.m_num, x.m_denum);
}
rational operator+(const rational&x, const rational&y){
    return rational(x) += y;
}
rational operator-(const rational&x, const rational&y){
    return rational(x) -= y;
}

rational operator*(const rational&x, const rational&y){
    return rational(x.m_num*y.m_num, x.m_denum*y.m_denum);
}
rational operator/(const rational&x, const rational&y){
    if(y.m_num > 0)
        // return {x.m_num*y.m_denum, x.m_denum*y.m_num};// No. cannot use without explicit use
        return rational{x.m_num*static_cast<int>(y.m_denum), x.m_denum*static_cast<int>(y.m_num)};
    return rational(-x.m_num*static_cast<int>(y.m_denum), x.m_denum*static_cast<unsigned>(-y.m_num));
}
bool operator == (const rational&x, const rational&y){
    return x.m_num*static_cast<int>(y.m_denum) == y.m_num*static_cast<int>(x.m_denum); 
}

bool operator < (const rational&x, const rational&y){
    return x.m_num*static_cast<int>(y.m_denum) < y.m_num*static_cast<int>(x.m_denum); 
}


bool operator != (const rational&x, const rational&y){
    return !(x==y);
}

bool operator <= (const rational&x, const rational&y){
    return (x<y)||(x==y);
}

bool operator > (const rational&x, const rational&y){
    return !(x<=y);
}

bool operator >= (const rational&x, const rational&y){
    return !(x<y);
}
int main()
{
    rational a;
    std::cin >> a;
    std::cout << ++a << std::endl; // ambiguous for user: double or class R?
    std::cout << a.to_double() << std::endl;
    std::cout << double(a) << std::endl;
    double b = a;
    std::cout << b << std::endl;
    return 0;
}