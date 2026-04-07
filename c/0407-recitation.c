/*
ptr, arr, mem
implicit convert, but UB when dereference with wrong type
deacy, nested array(array of array);
T(*)[10] and T(*)[100] are different types
strlen() -> size_t, which is an unsigned
str literal - read-only memory, but not const in C
addr - &"1234" is possible
malloc / calloc with 0 size - maybe NULL maybe ptr, derefer ptr -> UB, if not free ptr -> mem leak
free(0) harmless
*/

#include<stdio.h>

int main(){
    return 0;
}