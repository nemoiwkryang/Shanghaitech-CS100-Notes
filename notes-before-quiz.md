
# C 语言速查笔记

## main 函数与返回值

`main` 函数的返回值为 `return 0` 表示成功。

- ✅ **可以省略 `return 0`**  
  在 `main` 函数中，若执行到末尾无返回值，标准允许隐式返回 0。

- ❌ **在 non-void 函数中使用 `return;`**  
  未返回具体值 → **UB（未定义行为）**

- 多次声明(无函数体，可无变量名)，单次定义。

---

## 输入输出格式

### `printf` / `scanf` 格式与 `\n`

- 格式不匹配 → **UB**
- `%d` 会自动跳过前导空白字符

---

## 类型系统

### 赋值与类型

- 赋值给不支持的类型 → **CE（编译错误）**

| type        | >= Bytes | usually | format |
|-------------|----------|---------|--------|
| `char`      | 1        | 1       | `%c`   |
| `short`     | 2        | 2       | `%hd`  |
| `int`       | 2        | 4       | `%d`   |
| `long`      | 4        | 4/8     | `%ld`  |
| `long long` | 8        | 8       | `%lld` |

| type          | usually | format |
|---------------|---------|--------|
| `float`       | 4       | `%f`   |
| `double`      | 8       | `%lf`  |
| `long double` | 8+      | `%Lf`  |

- 为了防止**溢出**：优先使用 `/` 而非 `*` 等操作
- **`size_t`**：由实现定义，用于表示类型/对象大小

### 浮点比较

- ❌ **不要用 `==` 比较浮点数**
- ✅ **使用 `ε`如 1e-5 `abs()` 判断近似相等**

### 其他类型说明

- `char` 究竟是 `signed` 还是 `unsigned` → **实现定义**
- 布尔值：使用 `<stdbool.h>`

---

## 编码规范（Best Practice）

- **声明与使用尽量靠近**，不要隔太远
- **有意义的命名**
- **声明时初始化**，不要先声明再延后赋值
- **避免魔数（Magic Numbers）**，用宏或常量代替

### 代码简化

```c
// 冗余写法
a = ...;
return a;

// 简化写法
return ...;
```

---

## 运算符（OP）

### 优先级与隐式转换

- `double` 与 `int` 运算 → 提升为 `double`
- 短整型与长整型运算 → 提升为较长类型
- 小于 `int` 的整数类型 → 先提升为 `int`

### 取模运算 `%`

- `-5 % 3 == -2`
- `5 % -3 == 2`

### 优先级速记

**`!` > 比较运算符 > `&&` > `||`**

- 运算符优先级**不决定**变量求值顺序
- **例外**：`&&`、`||`、`?:` 具有确定的短路求值顺序
- 利用短路特性可避免部分 **UB**

---

## 未定义行为（UB）汇总

| 场景 | 说明 |
|------|------|
| ❌ **signed integer overflow** | 有符号整型溢出 |
| ❌ **修改同一对象多次** | 如 `i++ + ++i` |
| ❌ **既修改又读取同一对象** | 求值顺序问题 |
| ❌ **non-void 函数缺少 `return <value>`** | 未返回有效值 |
| ❌ **调用未初始化变量** | 值不确定 |
| ❌ **解引用 `NULL` 或 0** | 空指针解引用 |
| ❌ **野指针 / 悬空指针 / 无意义地址** | 非法内存访问 |
| ❌ **数组越界** | 访问 `[N]` 之后或 `[0]` 之前 |
| ❌ **指针相减超出数组范围** | 结果类型为 `ptrdiff_t` |
| ❌ **修改 `const` 变量** | 通过非 const 指针绕过 |

### 其他注意事项

- **unsigned 整型溢出**：定义良好（回绕），**不是 UB**
- **后缀与前缀 `++` / `--`**：注意返回值差异
- **`switch` fallthrough**：记得写 `break`；`case` 后必须是常量整型
- **`switch` 与 `do-while` 的作用域问题**：注意变量声明位置
- **`static` 局部变量**：仅初始化一次，生命周期贯穿程序

---

## 指针与数组

### 指针基础

- 地址类型：`uintptr_t`、`intptr_t`
- 数组隐式转换为指针，类型为 `T (*)[N]`
- 指针加减整数：按元素大小移动
- 指针移动到 `[N]` 之后或 `[0]` 之前 → **UB**

### 数组

- VLA（变长数组）目前部分环境不支持
- 支持嵌套初始化
- 传递指针到数组时，类型会检查维度（`int[3]` ≠ `int[2]`）
- 数组常被隐式转换为指针，但数组**不是**指针

### 数组返回方式

- `malloc` 动态分配
- 全局数组
- `static` 局部数组

### `const` 层级

- **低层 const**：指向的内容不可变
- **高层 const**：指针本身不可变
- 通过非 const 途径修改 const 变量 → **UB**

### 字符串

- 字符串以 `'\0'` 结尾
- 字符串字面量类型：`char *`（注意可写性历史问题） / `char []`
- 动态分配：`malloc`
- `%s` 以空白字符分隔读取
- 安全读取：`fgets(ptr, max_len, stream)`
  - 可读取\n, 长度包含\0(这半句是显然的)

### 内存管理

- **悬空指针**：`free` 后指针未置空
- `malloc` / `calloc` / 堆内存管理
- **嵌套 `malloc` 与 `free`**：注意逐层释放

### 字符串与字符处理函数

**`<string.h>`**

- `strlen` — 长度（不含 `\0`）
- `strcpy` — 复制
- `strcat` — 拼接
- `strchr` — 查找字符
- `strcmp` — 比较

**`<ctype.h>`**

- `isalpha`、`islower`、`isupper`
- `tolower`、`toupper`

**`<stdlib.h>`**

- `strtol` / `strtoll` / `strtoul` / `strtoull` / `strtof` / `strtod` / `strtold`

---

## 其他

- `printf("%p", (void*)p)` — 打印指针地址（函数指针除外）
- 命令行参数：`int main(int argc, char **argv)`

---

### C Struct
  - Syntax
    - declare a sturct:  struct Name {members};
    - declare an obj: struct StructName ObjName
      > struct necessary in C, use typedef otherwise
    - objName.memberName; ptr -> memberName, allocation, ...
      - `.` higher precedence than `*`
    - sizeof (struct Name) - more than the sum of member sizes
      > align with some specific numbers of Bytes
    - not explicitly init-d : all members obey the rules of their types (recursive)
      (global/static/heap - empty-init, local - un-init-d)
  - Init
    - initializer list
      {...}, or {.memberName = val} (after C99, not supported in C++17)
  - Param, Return, Assign 
    - Member-wise copy (recursive)
      - including arr - may replace memcpy
      > similar to deep copy in Python
    - ptr and addr for better performance
---

### C++ Introduction
- namespace, `using spaceName::name`, `using namespace spaceName`
- std::cin, std::cout in \<iostream>
  - std::cin.operator<<(var) prints and returns cin
- std::string in \<string>
  - auto init
  - convert from char*
  - possible ctor: (num, char), and copy ctor, ...
  - cin, cout, .operator+ with char* or std::string
  - .size(), .empty()
  - use +=, and -= instead of copying
  - .operator<=>
  - std::stoi, std::stol, ...
- \<c...> header files
- range-based for: for(ElemType var : Container), as if using var.operator=(*it)
  - container, arr, ref to arr, ...
  > (first, it++, *it, end)
- nullptr matching ptr
  > NULL may match int, implement-defined

---
  
- ref (mostly l-ref here) - useful in avoiding copy (efficiency or modify)
  - creating an alias, modify the object referred
  - should be init-d, otherwise *UB*
  - no rebind, no ref to ref
  - lref to lvalue (except const lref), rref to rvalue
    > const lref useful in passing tmp obj
    > otherwise rewrite a new function with rref
  - ref not object, (but lvalue)
  - using ref is the same to that object
    > similar to ptr but with some different op behaviors
    > rref = tmp, lref = rref, then lref refers to that tmp obj
  - array [] -> ptr, or ref to arr (&)[]
    > ref cannot be elem of arr
    > (&)[] means ref to arr
> lvalue not always obj, vice versa

- Declare and Init: Type */& (const, ...) Name[]/()
  - ()changing precedence > []/()function > prefix
  - Issues: Default Ctor: Name() is a function, not an instance constructed

- std::vector<T>
  - instantiation of class tmpl
  - init - ctor, copy ctor, (num), (num, val)
  - size, empty, push_back, pop_back, back, front, begin, end, at
  - pop_back, [], front, back no bound check -> *UB* possible
  > more methods see STL

- type cast
  - static_cast
    > usually "harmless", e.g. int. \<-> float., lval <-> rval
  - const_cast : removing low level const
    > modify causes *UB*
  - reinterpret_cast : ptr convert
    > ptr\<T1> to T2 - usually *UB*

- CTAD, auto and deduce
  - auto var - Cpp11+
  - auto func() - Cpp14+
  - CTAD - Cpp17+
  > auto params - Cpp20+
  - decltype(expr) -> type (compile time)

- function
  - default args : param = val
    - from L to R, default params in the end
    > ReturnType FuncName (P1, P2, ..., Px Q1 = V1, Q2 = V2, ..., Qy = Vy)
  - function overloading
    - rules: 
      - identical
      - decay of arr
      - high level const
      - low level const
      - int. or float. promotion
      - numeric conversion
        > just not promotion
      - class conv

### C++ Class / Struct
> Maybe see CS61b - many similarities to Java

- Basic Syntax:
  - Class or Struct Name{Attributes, Methods, public:, private: }
  - access: .mem, .memfun(...), ptr->...
  - this ptr in memfun
    - for memfun()const{}, decltype(this) is const Name* this
    - const member fun cannot and guarantees not to modify mem
      - only call const fun in const
      - const obj can only call const memfun
      - for const obj, mem - const Type, or Type *const
  > use const whenever possible
  
  - lifetime of non-static obj - see global/static/heap/global

- Ctor - Special member func
  - Syntax: T(params): mem(val), mem(val), ..., {...}
    - function declare, init list, statement
  - usually params const&
  - init order = declare order

  - copy ctor - accepts an obj (usually const T&)
    - if have extra resource, copy that in func statement
  - move ctor - accepts an rref to obj
    - if have extra resource, steal
  - copy and move ctor have special default behavior
    - call copy / move ctor recursively

  - no init - default
    > in statement, assignment

  - Default ctor
    - ctor taking in no param
    - behavior
      - const, ref cannot be default-init-d
      - class that cannot be default-init-d
      - other - each is default init-d,  see global, static, heap and local, (class in class behavior are defined recursively)
    - synthesizing default dtor
      - if cannot be default-initialized, no default ctor generated
    > For calling default ctor in declaring an obj, use `T var`
    
    > `T var()`, unfortunately, will be parsed as function declaration
    - no default ctor, and calling it - *CE*
  - explicit: =default, =delete - for any ctor

- Dtor
  - Syntax: ~T(){...}
    - every member are destroyed after the statements
    > the "last" time to interact with the members
  - destroy order - init_order.reverse()
  - default - dtor, recursive
    - explicit: =default, =delete

- Op overload
  - ReturnType operator Op (params) {...}
  - Copy assignment and move assignment (overload inside the class definition)
    - *this is the lhr
    - return T&
    - **self assignment safe!**
      > e.g. Dynarray - check same, delete[] old, new, co py

      > e.g. Dynarray - check same, delete[] old, ptr assign 
    - synthesized version - copy, recursive
  - explicit: =default, =delete
    - calling delete - 

- static mem, friend, using
  - using name = ElemType
    - In classes and public, use ClassName::name outside
    > e.g. containers usually have ...:size_type for size
  - static - shared by classes
    - use ClassName::name outside
    - static function - no *this, only modify static members
    - Obj.Name also works
    > application - counter
  - class / function declaration and definition
    - declaration needs no definition (约等于{}和其中内容)
    - define after declare
  - friend
    - friend declaration
      - usually for classes and functions to access private members
      - that is a declaration, not definition
        > e.g. not a function definition that needs statement
    - after that, define it outside of the class
  
- More about rvalue and rref
  - temporary obj, literal(except string literal)
  - can be bind to rref
  - rref extends their lifetime to the end of the scope
  - rref var is a lvalue
  - use std:move(x) to change lvalue to rvalue
    > in \<utility>
  - overloading: rvalue and lvalue do not cause ambiguity
    - basis of move ctor/assign possible
  - rvalue is something temporary
  - rref carries something temporary that may be destroyed soon

- Rule of Five
  - Copy, Move, Dtor should all be simuntaneously defined
  - compiler behavior: not generate if meets rules of 3 or 5
    - moves not generated if copy/dtor user-declared
    - copys deleted if move declared
    - dtor generation deprecated if copy or dtor declared

- NRVO, and other optimizing things
  - use reference when passing + assignment or just change assignment to param

### C++ STL - TBC