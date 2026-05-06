# ShanghaiTech CS100 课程笔记

> 基于 C17 和 C++17 标准 | 整合自 Lecture、Recitation 代码注释与随堂测验复习笔记\
> 使用Opencode + Deepseek V4 Pro总结
---

# 一、课程概述

- **目标**：学习与计算机交互、使用 C/C++ 解决问题、掌握正确语法、理解编程基本思想
- **结构**：讲座 + 讨论课；72% 作业(OJ) / 22% 期中 / 4% 随堂测验 / 2% 出勤
- **语言层次**：机器代码 ↔ 汇编代码 ←编译/解释→ 高级语言
- **标准**：C17 & C++17；参考 [cppreference.com](https://en.cppreference.com/)
- **工具**：[Compiler Explorer](https://godbolt.org/)（可视化编译输出）

---

# 二、编程哲学与开发理念

- 善用 LLM 辅助学习，但不可滥用；应当自己理解代码逻辑
- C/C++ 是**静态类型语言**：类型在编译时确定，必须先声明再使用

| 最佳实践 | 说明 |
|----------|------|
| 声明即初始化 | 避免使用未初始化的值（UB） |
| 就近声明 | 在使用前声明，缩小作用域 |
| 有意义的命名 | 使用描述性变量名 |
| 避免魔数 | `'n' - ('a' - 'A')` 而非 `'n' - 32` |
| 减少类型转换 | C++ 中用 C++ 风格转换，尽量少转 |
| 使用格式化工具 | 保持代码风格整洁 |

---

# 三、C 语言基础

## 3.1 历史与编译

- AT&T 贝尔实验室，K&R C，与 UNIX 紧密相关
- 标准化：C89 → C99 → C11 → **C17** → C23
- 编译：`.c` → `gcc -std=c17` → 可执行文件
- `gcc --save-temp`：保留预处理(.i)、汇编(.s)、目标文件(.o)

## 3.2 函数与 main

```c
<返回类型> <函数名>(<参数列表>) { <函数体> }  // 无参数用 void
```

```c
int main(void) { return 0; }   // 入口点，return 0 正常结束
```

- **不推荐** `void main()`；非 void 函数缺 return 是 **UB**
- `()` 是函数调用运算符；可多次声明但只能定义一次

## 3.3 输入输出

| printf | scanf | 类型 |
|--------|-------|------|
| `%d` | `%d` | int |
| `%lf` | `%lf` | double |
| `%s` | `%s` | 字符串 |
| `%p` | — | 指针(需转 `(void*)`) |

**scanf 要点**：
- `%d` 自动跳过前导空白；`" %c"` 可在读字符时忽略空白
- `"%d\n"` 中的 `\n` 会跳过后续所有空白，**永不结束**
- 格式不匹配 → **UB**

**字符串输入**：`scanf("%s", ...)` 不检查溢出；`gets()` C11 已移除；推荐 `fgets(s, len, stdin)`

## 3.4 数据类型

### 整数类型

| 类型 | 最小字节 | 典型字节 | 格式 |
|------|:-------:|:-------:|------|
| short | 2 | 2 | `%hd` |
| int | 2 | 4 | `%d` |
| long | 4 | 4/8 | `%ld` |
| long long | 8 | 8 | `%lld` |

- 无符号加 `u` 后缀；n 位范围：unsigned `0~2^n-1`，signed `-2^(n-1)~2^(n-1)-1`
- 实际宽度**实现定义**；低于 int 的类型自动提升为 int
- **有符号整数溢出是 UB**；无符号溢出回绕

### 浮点类型 (IEEE 754)

| 类型 | 字节 | 格式 |
|------|:----:|------|
| float | 4 | `%f` |
| double | 8 | `%lf` |
| long double | 16(实现定义) | `%Lf` |

- float/double **≠ 实数**，比较用 `ε` + `abs()` 而非 `==`

### char / bool / sizeof

```c
char ch = 'A';            // 1 字节 ASCII；signed/unsigned 实现定义
#include <stdbool.h>
bool flag = true;          // C99+；或直接用 1/0
sizeof(类型) / sizeof 变量  // 返回 size_t
```

### 字面量与左右值

- 整数字面量默认 `int`，后缀 `u/l/ll`；浮点默认 `double`，后缀 `f/l`
- **没有负的整数字面量**：`-42` = 一元负号 + 字面量 `42`
- **左值**：可出现在赋值左侧（有地址）；**右值**：只能出现在右侧

## 3.5 运算符

| 类别 | 运算符 | 优先级/备注 |
|------|--------|------------|
| 算术 | `+ - * / %` | 一元 +/- > *,/,% > 二元 +/- |
| 赋值 | `= += -= *= /= %=` | — |
| 自增减 | `++i`(先加后用) / `i++`(先用后加) | — |
| 比较 | `== != < > <= >=` | — |
| 逻辑 | `! > 比较符 > && > \|\|` | **短路求值** |
| 条件 | `? :` | — |
| 位运算 | `~ & \| ^ << >>` | — |

**关键规则**：
- `(a/b)*b + (a%b) == a`；C99+ 结果符号与被除数同
- 短路求值：`a&&b` a 为假则停；`a\|\|b` a 为真则停
- 实用技巧：`if (p != NULL && *p == val)` 安全访问
- **仅 `&& || ?: ,` 保证求值顺序**；其余运算符的操作数求值顺序未规定
- **UB**：`++i + i++`、`i = i++ + 2` 等同表达式多次修改/读取同一变量

## 3.6 类型转换

- 隐式：`double + int → double + double`；短类型向长类型转
- 类型不匹配的指针解引用 → **UB**

## 3.7 控制流

```c
if (<条件>) <语句> else <语句>
while (<条件>) <语句>                    // 技巧：while(--n) 执行 n 次
for (init; cond; iter) <语句>            // 循环内变量作用域仅限循环体
do { <语句> } while (<条件>);            // 注意作用域问题
switch (expr) { case 常量: ... break; default: ... }  // case 须为整数常量；注意 fallthrough
```

- `break`：跳出当前循环/switch；`continue`：跳过本次迭代

## 3.8 函数进阶

**作用域**：全局 → 函数 → 块 → 嵌套块（就近声明原则）

```c
int global_var;                    // 自动初始化为 0
void func() {
    static int count = 0;          // 仅初始化一次，跨调用保持值
    count++;
}
const int MAX = 100;              // 常量，修改 → UB
```

## 3.9 指针

```c
int i = 42, *p = &i;     // & 取地址→类型*，* 解引用→左值
printf("%d", *p);         // 42
```

- `NULL` / `0`；C23/C++11 推荐用 `nullptr`
- 未初始化的局部指针 = **野指针**；解引用 NULL/野指针 → **UB**
- 全局/静态指针自动初始化为 NULL

**传值 vs 传地址**：

```c
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }  // 传地址可修改原变量
```

**指针算术**：

```c
int a[10], *p = a;
p + i;     // 偏移 i*sizeof(int) 字节，指向 a[i]
p[i];      // 等价 *(p+i)；a[i] ⇔ i[a]
p - a;     // ptrdiff_t（有符号）
```

- 指针越界解引用 → **UB**；不同数组指针相减 → **UB**
- 允许指向 `a[N]`（尾后），但不可解引用

**const 与指针**：

```c
const int *p;          // 底层 const：不能通过 p 修改值
int * const p;         // 顶层 const：p 不可改指向
const int * const p;   // 两者
```

**void 指针**：可指向任意类型；printf 用 `%p` + `(void*)`；C++ 中不可隐式转出

**嵌套数组与指针**：

```c
int b[10][10][10];
int (*q)[10][10] = b;   // T (*p)[N]：指向数组的指针
int (*r)[10] = b[1];    // T *p[N]：指针数组（不同类型！）
// int ***q = b;         // 错误：嵌套数组 ≠ 指针的指针
```

**返回数组**：指向全局/malloc分配/static 数组的指针

## 3.10 数组

```c
int a[5] = {1,2,3,4,5};          // 完全初始化
int b[5] = {0};                   // 全零
int c[] = {1,2,3};                // 自动推断大小
int d[10] = {[0]=1,2,3,[6]=7,8}; // 指定初始化
```

- 全局/静态数组自动初始化为 0；越界 → **UB**
- **VLA**（变长数组）：C99 支持，C11 可选，**本课程不推荐**，用 `calloc` 替代
- 数组作函数参数时**退化为指针**，`sizeof` 返回指针大小；需额外传大小

## 3.11 字符串

```c
char s[] = "Hello";    // 字符数组（可修改）
char *s = "Hello";     // 字符串字面量（只读！修改 → UB）
```

- 以 `'\0'` 结尾，字面量自动添加；字面量在 C 中非 const 但不可修改，C++ 中为 `const char[]`

**输入输出**：`fgets(s, len, stdin)` 推荐；`puts(s)` 输出并换行

**`<string.h>`**（均为 O(n)）：

| 函数 | 功能 |
|------|------|
| `strlen(s)` | 长度（返回 `size_t`，无符号） |
| `strcpy(dest, src)` | 复制 |
| `strcat(dest, src)` | 拼接 |
| `strcmp(s1, s2)` | 比较（0=相等） |
| `strchr(s, c)` | 查找字符 |

**数值转换**（`<stdlib.h>`）：`strtol`、`strtoll`、`strtoul`、`strtod` 等

## 3.12 动态内存

- **栈**：局部变量，自动管理；**堆**：动态分配，手动管理，生命周期不受作用域限制

```c
int *p = (int*)malloc(sizeof(int) * 10);  // 不初始化
int *p = (int*)calloc(10, sizeof(int));    // 初始化为 0，适合数组
free(p); p = NULL;                         // free(NULL) 无害；free 后置 NULL 避免悬垂指针
```

- `malloc(0)`：实现定义，可能返回 NULL 或不可解引用的指针
- 检查 NULL 检测 OOM

**二维动态分配**：
```c
// 连续内存（缓存友好）
int *p = malloc(n * m * sizeof(int));  p[i*m+j] = ...;  free(p);
// 指针数组（p[i][j] 语法）
int **p = malloc(n * sizeof(int*));  for(i) p[i] = malloc(m * sizeof(int));
```

## 3.13 预处理器

- `#include`：本质文本替换；`<>` 系统目录，`""` 当前目录优先
- `#define PI 3.14` / `#define MAX(a,b) ((a)>(b)?(a):(b))`：宏参数加括号

## 3.14 结构体

```c
struct student { int age; int stuNum; };
struct student s = {.age = 20, .stuNum = 1001};  // 指定初始化
struct student *p = &s;  p->age;                  // -> 等价 (*p).age
```

- **内存对齐填充 (padding)**：成员排列顺序影响大小
  - `int(4)+char(1)+double(8)` → 16 字节（+3 padding）
  - `char(1)+double(8)+int(4)` → 24 字节（+7+4 padding）
- 作为参数/返回值是**深拷贝**（可利用此特性复制数组：`b = a;`）

## 3.15 命令行参数

```c
int main(int argc, char *argv[]) { ... }
// argv[0]=程序名，argv[argc]=NULL
```

## 3.16 `<ctype.h>`

| `isdigit` | `isalpha` | `islower` | `isupper` | `tolower` | `toupper` |
|-----------|-----------|-----------|-----------|-----------|-----------|

---

# 四、C++ 语言

## 4.1 概述

- "C with Classes" → Templates → STL；C++98 → C++11 → C++14 → **C++17** → C++20/23

## 4.2 "Better C" 改进

| 特性 | 说明 |
|------|------|
| `bool`/`true`/`false` | 内置，无需 `<stdbool.h>` |
| `nullptr` | 替代 NULL（NULL 可能是 int 0） |
| 字符字面量 | `'a'` 是 `char`（C 中是 `int`） |
| 严格类型检查 | 有风险的隐式转换报错 |
| const 编译期常量 | 可用于数组长度 |
| 空参数列表 | `()` = 0 个参数（C 中 = 未指定） |

## 4.3 头文件与命名空间

- C++ 头文件无 `.h`：`<iostream>` `<vector>` `<string>`
- C 库对应版本：`<cstdio>` `<cstdlib>` `<cstring>`（声明在 `std` 命名空间）
- `using std::cin;` / `using namespace std;`（**不要在头文件全局使用**）

## 4.4 I/O 流

```cpp
std::cin >> x >> y;              // 链式调用，返回 cin/cout
std::cout << x << '\n';          // 无需格式字符串
std::cout << x << std::endl;     // endl = '\n' + 刷新缓冲区
```

- 缓冲区满/手动刷新时才真正输出；崩溃时未刷新内容丢失

## 4.5 `std::string`

```cpp
std::string s;                   // 空（自动初始化）
std::string s(3, 'n');           // "nnn"
s.size(); s.empty(); s.clear();
s += " World";                   // 原地拼接（高效）；s = s + "!" 创建临时对象
// s = "a" + "b" + s;            // 错误！至少一个操作数须为 std::string
if (s1 < s2) { ... }             // 字典序比较
std::cin >> s;                   // 遇空白停；getline(cin, s) 读整行
// cin >> s 后接 getline 需先 cin.ignore() 处理残留 \n
std::stoi("123"); std::to_string(3.14);  // 数值转换
```

## 4.6 `std::vector`

```cpp
std::vector<int> v(10, 2);       // 10 个元素，值为 2
std::vector v = {1,2,3};         // C++17 CTAD 自动推导类型
v.size(); v.empty(); v.clear();
v.push_back(x); v.pop_back();
v.front(); v.back();             // 返回引用
v[i];                            // 不检查边界(UB)；v.at(i) 检查但慢
v.capacity();                    // 已分配内存容量
```

- range-for 时不要同时 `push_back`（迭代器可能失效）

## 4.7 引用 (Reference)

```cpp
int a = 42;  int &ref = a;       // ref 是 a 的别名
```

| 特性 | 说明 |
|------|------|
| 必须初始化 | `int &r;` → 编译错误 |
| 不可重绑定 | 始终指向同一对象 |
| 须绑定左值 | `int &r = 1;` → 错误（`const int &r = 1;` 可以） |

- 函数参数传引用替代 C 的传指针：`void swap(int &a, int &b)`
- range-for 引用修改：`for (char &c : str) { c += 1; }`
- 引用可绑定到指针（`int *&ref = p`），但不存在"指向引用的指针"

## 4.8 类型推导与转换

```cpp
auto i = 42;              // int；C++14+ 可作返回类型
decltype(x) y = 1;       // 推导类型但不求值

static_cast<T>(expr)      // 良性转换（int↔double, void*↔T*）
const_cast<T>(expr)       // 移除/添加 const
reinterpret_cast<T>(expr) // 重解释位模式（危险）
dynamic_cast<T>(expr)     // 运行时多态向下转换
```

**原则**：尽量减少转换，必须时用 C++ 风格

## 4.9 函数进阶

**默认实参**（必须在最右）：`int fun(int x, int y = 0);`

**函数重载**——解析优先级：
1. 精确匹配（含 decay、顶层 const）
2. 底层 const 匹配
3. 整型/浮点提升（bool/char→int, float→double）
4. 其他转换（int↔long, signed↔unsigned）

**传数组引用**：`void fun(int (&a)[10])` 保留数组大小信息

## 4.10 类 (Class)

```cpp
class Stu {                          // 默认 private（struct 默认 public）
    std::string name{"Test"};        // 类内初始化：用 {} 或 =
    const int year;
    const int &ref;
public:
    Stu(const std::string &n, int y)
        : name(n), year(y), ref(y) {}   // 初始化器列表：真正初始化，先于函数体
    // 初始化顺序 = 成员声明顺序（非列表书写顺序）
    void printName() const { ... }      // const 成员函数：不可修改成员
    ~Stu() { ... }                      // 析构函数：对象生命周期结束时自动调用
};
```

**不可默认初始化的成员**（必须用初始化器列表）：引用、const 内置类型、无默认构造函数的类成员

**默认构造函数**：
- 无用户声明构造函数 → 编译器合成（有不可默认初始化成员则放弃 → CE）
- 用户声明后不再合成；需显式 `Stu() = default;`
- `= delete` 禁用

**new / delete**：

```cpp
int *p = new int(42);    int *arr = new int[10]{};
delete p;                 delete[] arr;      // 不匹配 → UB
```

**静态成员**：`static int count;`（类外定义 `int Stu::count = 0;`）；所有实例共享

## 4.11 复制语义

- 默认行为 = 逐成员复制（含指针时为**浅拷贝**）

```cpp
DynArray(const DynArray &other);              // 拷贝构造：参数用 const& 避免递归
DynArray &operator=(const DynArray &other);   // 赋值运算符：注意自赋值
DynArray(const DynArray &) = delete;          // 禁用拷贝
```

**三法则 (Rule of 3)**：若需自定义析构/拷贝构造/拷贝赋值之一，则很可能需自定义全部三个

## 4.12 类型别名

```cpp
typedef int Integer;          // C 风格
using Integer = int;          // C++ 风格（推荐）
class MyClass { using value_type = int; };  // 类内别名 → MyClass::value_type
```

---

# 五、常见未定义行为 (UB) 总览

| 分类 | 具体情形 |
|------|----------|
| 整数运算 | 有符号整数溢出 |
| 数组操作 | 越界访问 |
| 指针操作 | 解引用 NULL / 野指针 / 悬垂指针 |
| 指针操作 | 不同类型指针隐式转换后解引用 |
| 指针运算 | 越界解引用；不同数组指针相减 |
| 未初始化 | 使用未初始化的局部变量 |
| 表达式 | 同表达式多次修改/修改并读取同一变量（`++i+i++`） |
| 函数 | 非 void 函数缺 return |
| I/O | printf/scanf 格式与参数类型不匹配 |
| const | 修改 const 变量 |
| 字符串 | 修改字符串字面量 |
| 动态内存 | 解引用已释放内存；`delete`/`delete[]` 混用；解引用 `malloc(0)` 返回的指针 |

**安全编程**：用 `fgets` 替 `gets`、指针解引用前判 NULL、开启 `-Wall -Wextra`

---

# 六、调试与工具

| 调试操作 | 含义 |
|----------|------|
| Breakpoint | 暂停执行 |
| Continue | 运行到下个断点 |
| Step Over / In / Out | 单步 / 进入函数 / 跳出函数 |

```bash
gcc -Wall -Wextra -std=c17    # 警告 + 标准
gcc --save-temp               # 保留中间文件
```

---

# 七、参考资源

- [cppreference.com](https://en.cppreference.com/) — [C 字符串函数](https://en.cppreference.com/w/c/string/byte.html) | [C++ string](https://en.cppreference.com/w/cpp/string/basic_string)
- [Compiler Explorer](https://godbolt.org/) — 编译器探索工具