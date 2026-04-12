/*
int main (int argc, char **argv){}
argv *[] ends with additional NULL

struct
struct <name> {
    declar 1
    2
    ...

};
these var complex types are usually called obj

use "." to access a member of struct
<name>.<name>
the struct name is a "tag", not always like a "type":

    declare - struct <tagName> <varName>,
    sizeof(struct <tagName>) 

    malloc and ptr possible

    sizeof -> not always same as look like
        reason - padding
        4 + 1 + 8 -> 4+1 +3(padding) +8
        1 + 8 + 4 -> 1 +7(padding) +4 +4 (padding)
    roughly description - align with 8 Bytes
    -> see CA, OS, and Compiler

initialization -> like other types
initializer list {.<attrbName>=...} or {..., ..., ...}, also named compound literals
passed as param - deepcopy / memwise - not list passing as python, so does return values

application - copy an array

for ptr to struct - use ptrName->attrName
*/

#include<stdio.h>

struct stu{
    int age;
    int stuNum;
};

int main(int argv, char *argc[])
{
    int i=0;
    while(argc[i]!=NULL){
        printf("%s\n",argc[i]);
        i++;
    }
    return 0;
}