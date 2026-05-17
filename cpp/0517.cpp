

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<numeric>

/*
lec 20 - iterator and algorithm

# iterator
- generalized pointer, can be used to access elements in a container
- type - Container::iterator
    e.g. std::vector<int>::iterator, auto useful here.
- operations, for container c
    - c.begin(), c.end() - return an iterator to the first element and one *past the last element* (ptr + length)
    > [begin, end)
    left-inclsive, right-exclusive
    - useful for length and empty check
        - e-b
        - b == e
- operations, for iterator it
    - *it - dereference, get the element
    - it++ or ++it - move to the next element
    - it->member - access member of the element, if the element is a struct or class
    - ==, != - compare two iterators, check if they point to the same position
> supported by all stl containers with sequential access, e.g. vector, list, deque, set, map, etc.

- application:
    - traverse a container

- for built-in ptr, used as it for arr
    > for ElemType a[N], a, a+N
    - std::begin(a), std::end(a) returns begin / end for both array (-> ptr) and container (-> it)

- range-based for loop == iterating
    - for (auto &elem : container) {} equivalent to for (auto it = container.begin(); it != container.end(); ++it) { auto &elem = *it; ... }

- dereferenceable - like ptr, *v for v end cause UB, so does move it outside
    e.g. it to *ptr assigned by new, gets invalidated when delete ptr
    e.g. push_back(realloc) / pop_back(invalidate the last)
    e.g. for traversing a vector while doing some push_back()-s, use ptr instead of range-based for loops

- more about types and op
    - ForwardIterators - *, ->, ++, ==, !=
    - BidirectionalIterators - -- also OK
    - RandomAccessIterators - .op+, .op-, .op[] (n), .op <=>, -(it)

    e.g. built-in pointer, string it, vector it - random
    e.g. list - bidir
    e.g. forward_list - forwrd

- init from it range
    container Name(it_b, it_c)

*/

void test_for_it(){

    std::vector<int> v{};
    // iterator
    std::vector<int>::iterator it_b = v.begin(), it_e = v.end();
    std::cout << "empty: " << std::boolalpha << (it_b == it_e) << std::endl;
    v = {1, 2, 3};
    std::cout << "length: " << it_e - it_b << std::endl;

    // ---

    std::string s = "HeLlo,WorLD!";

    for(auto it = s.begin(); it != s.end(); ++it){
        std::cout << static_cast<char>(std::islower(*it) ? *it : std::tolower(*it)) << " ";
    }
    std::cout << std::endl;
}

/*
just the commonly-used ones, 'cause no one remember all of the stl algo (unless u crazy 'bout ACM, XCPC, OI, or smth)
- usage 
    - for many, std::...(it_b, it_c)
        > cpp20 and later - std::ranges::Name(...), more modern traverse
    e.g. 
        copy(it_b, it_e, it_dest)
            useful for range ctor for Dynarray
        copy_n(it_src, length, it_dest)
            useful for Dynarray copy ctor
        fill_n(it_b, length, num)
            useful for Dynarray ctor (length, val)
    
    - for many, std::... -> it for the position (.end for not found)
        e.g. find(it_b, it_c, val), maxPos(it_b, it_c)
        therefore, check end before deref

    used in if after cpp17
        syntax - if(expr(usually declare smth); condition)
        scope of declared - the whole statement (if - else)

    - for many - require special types of it, e.g. random, bi, forwr, ...
        e.g. sort <- random
        e.g. all algo requiring cmp need < and ==
    
    - for most - never modify length, insert or delete
        e.g. copy(it_b, it_c, it_to_less_size) -> UB, just like std::strcpy(ptr, ptr)

# common algo
    count, find, find_end \(start from last\) (begin, end, x)
    find_first_of(begin1, end1, begin2, end2, [cmp]) to find any of elem in 1 that equals(or cmp()) to any elem in 2
    search(begin, end, pttrn_begin, pttrn_end)

    ---

    copy(), fill, reverse, 
    unique() -> pos for end unique elem (start of duplicated elem, or end if no duplicate) (just not delete)

    partition, is_partitioned, stable_partition
    sort, is_sortedm stable_sort
    nth_element
    merge, inplace_merge

    lower_bound, upper_bound, binary_search, equal_range
    is_heap, make_heap, push_heap, pop_heap, sort_heap

    - more in CS101

    min_element, maxelement, minmax_element -> pair<T, T>
    equal(begin1, end1, begin2, [end2])
    lexicographical_compare(begin1, end1, begin2, end2)

# in <numeric>
    accumulate(begin, end, initVal) = sum(begin, end) + initVal
    inner_product(begin1, end1, begin2, initValue) - vector(for real, not dynarray) inner_product a^T·b + initVal

# predicate - used as cmp like the subtitute for op < 
    for cmp(), may use (it, it, ..., cmp) use cmp instead of <
    e.g. use sort for descending ordr
    cmp is a callable obj
    lumbda functions accepted
    e.g. find_if(begin, end, p)

    other callable obj 
        e.g. for_all(begin, end, oper)) performs op(elem)
        as if for(auto &i:...){op(i);}

    if condition involving runtime-determined value:
        - lumbda
        - struct ctor with runtime val and op() overload
        - a function obj (functor) is an obj with op() overloaded
        - any number of args allowed
    more about lumbda
        [capture_list (ref or not, varName, sep-ed by comma)](params) -> auto / none / Type{}, type can be deduced
        creates temporary function obj


---

### in short, algorithms in stl features
- without insert/delete
- accepts it range [begin,end)
- _n accepts(it, length) as for [begin, begin + length)
- predicate for customized cmp
- _if requires that predicate
- common ones - find, for, sort, copy, unique, ...


*/

bool cmp(const int &a, const int &b){
    return a > b;
}

void test_for_algo(){
    std::vector<int> a={1,2,3,3,1,4,8};
    auto endpos = std::unique(a.begin(),a.end());

    for(const auto &i:a){
        std::cout << i;
    }
    std::cout << std :: endl;

    a = std::vector(a.begin(), endpos); // better use vector.erase(it_b, it_e)
    for(const auto &i:a){
        std::cout << i;
    }
    std::cout << std :: endl;

    std::sort(a.begin(), a.end(), [](const int&a, const int&b) -> bool{return a>b;});
    std::sort(a.begin(), a.end(), cmp);
    for(const auto &i:a){
        std::cout << i;
    }
    std::cout << std :: endl;
}

int main(){
    test_for_it();
    test_for_algo();
    return 0;
}