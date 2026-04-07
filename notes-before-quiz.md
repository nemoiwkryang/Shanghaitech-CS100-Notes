
main, function preview; return value
`return 0` if successful
### omit `return 0` in main✅
### use "return;" not in void ❌ **UB**

### printf, scanf format, \n - wrong format **UB**
- %d skip leading whitespace

### assign to unsupported type -> **CE**

### Best practice - declare and use lines not seperated
### meaningful names
### init with declare, instead of later assign

char, short, int, long, long long; signed, unsigned
| type | >= Bytes | usually | format |
| --- | --- | --- | ---|
| char | 1 | 1 | %c |
| short | 2 | 2 | %hd|
| int | 2 | 4 | %d|
| long | 4 | 4/8 | %ld|
| long long | 8 | 8 | %lld|
| float ||4| %f|
| double ||8| %lf|
| long double |8||%Lf|

from smallest size to largest
**About overflow - use / than \*, ...**
**size_t - implement-def, for type size**

### float types - use $\epsilon$ and abs(), not ==
### implement - define
### Best practice -avoid magic numbers
\ + characters used in format, or cannot be typed
escape sequence
### char = signed / unsigned : implementation - defined

### stdbool.h
### simplify code - a=...; return ...; -> return ...;

---

OP
### precedence and implicit convert
double with int -> double
shorter with longer size-> longer size type
% -> -5%3=-2, 5%-3=2
integers with less than int -> int

### signed integer overflow **UB**
### unsigned integer not overflow
### postfix and prefix ++/--
### OP precedence
**! > cmp > && > ||**
do not determine the evaluation order of var
**except && || ?:**
**This may avoid UB**

### Evaluation **UB** - modifying same obj, or modify and call it
### switch fallthrough - remember `break`; case \<const int>
### the problem of scope in switch and do-while
### non-void without "return \<value>" - **UB**
### Scope and namelookup
### static (init only once)
### call un-init-ed var **UB**
---
### NULL or 0 - dereference **UB**, so does wild ptr, dangling ptr, meaningless addr
> addr type - uintptr_t, intptr_t
### array - VLA not supported for now; init; nested
### array out of range **UB**
### pointer subtract pointer not within array **UB**
return type - ptrdiff_t
### pointer op int movement
### array implicit convert to ptr, and Type (*)[]
### pointer moved to after then [N] or before [0] **UB**
### return array - malloc / global / (static)
### pass pointer to array will be checked (int[3] != int[2])
### const low and high level; modify const var **UB**
### dangling ptr, free, malloc, calloc, heap memory
### '\0', string literal, char *, char [], malloc
### %s seperated whitespace; fgets(ptr, maxL_arr, stream)
### string.h
- strlen
- strcpy
- strcat
- strchr
- strcmp
### ctype.h
- isaplha
- islower
- isupper
- tolower
- toupper
- strtol/ll/ul/ull/f/d/ld

### printf %p - (void*)p, except ptr to func
### nested malloc and free
### cmd - int main(int argc, char ** argv)