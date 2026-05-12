/*
smart pointers - concept, unique_ptr, and shared_ptr
    concept - auto delete

what if copy ? 
    1. copy obj (like dynarray(1) and normal types)
    2. copy ptr (shared_ptr, introduce count to prevent delete disaster)
    3. disable copy (unique_ptr); move available

usage: *, and ->; convertible to bool representing not null
defined in <memory>

unique_ptr, shared_ptr are templates, not classes

declare
    - ctor of unique_ptr<T>
    std::unique_ptr<T> p(new T(...));
    - function template make_unique<T>
    - default (null initialize)
usage
    auto dtor of T instance called
    auto dtor of unique_ptr<T> instance called
    move_only
    want copy obj ? new / make_unique
    want raw pointer ? unique_ptr<T>.get() -> T*; be careful with it
    other op : reset, release, swap, ==
    for array, better use stl containers
        for array, use <T[]>
            [] availeble, but not * or ->
stores no more than ptr, and nothing else, just check and dtor, normal move

---

std::shared_ptr - multi access to a ptr
    when to dtor? reference counting

better use make_shared than new
usage - *, ->, .use_count, ...; has time and space overhead

! for chained-list, due to a1<->a2<->a3, simple reset the pointer that points to a1 will not destroy the deque -> memory leak of the whole deque (cnt is still 1, not 0)
*/

#include<iostream>
#include<string>
#include<vector>
#include<memory>

class autoPtr_unique
{

    int *ptr;
public:
    autoPtr_unique(int *ptr = nullptr):ptr(ptr){}
    ~autoPtr_unique(){delete ptr;}

    /* what if copy? */
    autoPtr_unique(const autoPtr_unique&) = delete;
    autoPtr_unique &operator = (const autoPtr_unique&) = delete;

    autoPtr_unique(autoPtr_unique && other)noexcept
    :ptr(other.ptr){other.ptr = nullptr;}
    autoPtr_unique &operator = (autoPtr_unique && other)noexcept{
        if(this == &other)return *this;
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

};

class autoPtr_shared
{
// pointer to struct
// struct that contains ptr and cnt
public:
    // autoPtr_shared(int *ptr = nullptr):ptr(ptr){}
    // ~autoPtr_shared(){delete ptr; ptr->cnt--}

    // /* what if copy? */
    // copy ctor: ptr->cnt++,
    // copy assign op :
    // if not self:
        // ptr->cnt--, if 0 delete, other.ptr->cnt++, ptr = other.ptr
    // dtor: ptr->cnt--, if 0 delete
    // move assign - previous->cnt--, if 0 delete, steal other

    // autoPtr_shared(autoPtr_shared && other)noexcept
    // :ptr(other.ptr){other.ptr = nullptr;}
    // autoPtr_shared &operator = (autoPtr_shared && other)noexcept{
    //     if(this == &other)return *this;
    //     delete ptr;
    //     ptr = other.ptr;
    //     other.ptr = nullptr;
    //     return *this;
    // }

};

int main()
{
    autoPtr_unique a(new int);

    std::unique_ptr<int> p(new int(0));
    std::unique_ptr p1 = std :: make_unique<int>(1);
    auto p2 = std::move(p1);
    std::cout << p1.get() << std::endl; // 0

    auto parray = std::make_unique<int[]>(10);

    for(int i=0;i<10;i++)std::cout << parray[i] << std::endl;

    // std::cout << *parray << std :: endl; unavailable

    return 0;
}
