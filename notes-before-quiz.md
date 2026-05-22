# CS100 Quiz 前速查

> `【习题课补充】` 标记表示来自 `Recitation Slides` 的额外内容。

## 0. 这不是我的错，也不一定是你的错

- `CE`: 编译错误 / 语义错误 / 调用被删除的函数。
- `UB`: 未定义行为，结果不可靠。
- `ID`: 实现定义，取决于编译器/平台。

| 情况 | 结论 |
|---|---|
| `return;` 出现在 `non-void` 函数里 | `CE` |
| C: `non-void` 函数走到末尾且返回值被使用 | `UB`，`main` 例外 |
| C++: `non-void` 函数走到末尾 | `UB`，`main` 例外 |
| `int &r = 42;` | `CE` |
| `const int &r = 42;` | `OK`，临时对象生命周期延长 |
| `a + N` | `OK`，one-past-the-end，不可解引用 |
| `a - 1` 或跨数组做指针运算 | `UB` |
| `signed` 溢出 | `UB` |
| `unsigned` 溢出 | 定义良好，回绕 |
| 局部未初始化变量被使用 | `UB` |
| `std::unique_ptr` 被复制 | `CE` |
| `std::shared_ptr` 形成环 | 可能泄漏 |

---

## 1. C 语言

### 1.0 预处理

- 【习题课补充】`#include` 本质上是文本替换，不是“聪明的导入”。
- 【习题课补充】`#define` 也是文本替换；函数式宏要给参数和整体都加括号，但仍可能重复求值，能不用就不用。
- 【习题课补充】`typedef` 是类型别名，别用 `#define` 代替。

### 1.1 函数与返回值

- `main` 返回 `0` 表示成功。
- 在 `main` 末尾直接结束，等价于 `return 0;`。
- `void` 函数不返回值；`non-void` 函数的正常返回路径应 `return expr;`。C 中返回值被使用时 `UB`；C++ 中走到末尾就是 `UB`；`main` 例外。
- 函数声明只写返回类型、函数名、参数类型并以 `;` 结尾；定义包含函数体。
- 同一函数可多次声明，只能定义一次。
- 【习题课补充】C 里无参数函数写 `f(void)`；空参数列表历史上表示“参数未知”。

### 1.2 输入输出

- `printf` / `scanf` 的格式和实参类型必须匹配，错配通常是 `UB`；`scanf` 的返回值应检查，确认读入成功。
- `scanf("%d")` 会跳过前导空白。
- `scanf("%c")` 会读到空白字符本身。
- `printf` 常用格式：`%d`、`%ld`、`%lld`、`%c`、`%f`、`%s`、`%p`；`%f` 用于浮点输出。
- `scanf` 常用格式：`%d`、`%ld`、`%lld`、`%f`(float)、`%lf`(double)、`%c`、`%s`；`%f` 读 `float *`，`%lf` 读 `double *`。
- `scanf` 读指针参数时通常要传地址；`%s` 对字符数组是例外。
- `printf("%p", (void*)p)` 打印指针地址，函数指针除外。
- `fgets(buf, n, stream)` 比 `scanf("%s")` 更安全，最多读入 `n-1` 个字符并补 `\0`，可能保留换行。
- 【习题课补充】`freopen` 可以在程序里重定向 `stdin` / `stdout`；`fopen` / `fclose` / `fscanf` / `fprintf` 这类函数围绕 `FILE *` 使用。
- 【习题课补充】`getchar()` 搭配 `isspace` / `isdigit`，常用于逐字符读入未知长度输入。

### 1.3 类型与运算

- `char` 的 signedness 是实现定义。
- `size_t` 用来表示对象大小，类型由实现决定。
- C 中布尔值用 `<stdbool.h>`；C++ 里是内建类型。
- 【习题课补充】普通字符字面值 `'a'` 在 C 里类型是 `int`；在 C++ 里类型是 `char`。
- 小于 `int` 的整数类型在表达式中通常先提升为 `int`。
- `int` 和 `double` 运算会提升到 `double`。
- `short` / `char` / `bool` 之类常先做整数提升。
- 有符号整型溢出是 `UB`；无符号整型溢出按模回绕。
- 除法向 0 截断，余数满足 `(a / b) * b + (a % b) == a`。
- 余数的符号和被除数一致：`-5 % 3 == -2`，`5 % -3 == 2`。
- 浮点数比较不要直接写 `==`，用 `fabs(a - b) < eps`。
- C 里用 `fabs` / `fabsf` / `fabsl`；C++ 里可用 `std::abs` 或 `std::fabs`。
- 【习题课补充】位运算 `~ & ^ | << >>` 常用于掩码；对无符号数更安全，`a & 1` 可快速判断奇偶。
- 优先级不决定求值顺序；`&&`、`||`、`?:`、`,`（不在函数调用和初始化列表中）有确定的短路/求值顺序。
- 若两个未定序求值中，一个修改对象，另一个读取或修改同一标量对象，就是 `UB`，例如 `i++ + ++i`。
- `switch` 的 `case` 必须是常量整型表达式；忘记 `break` 会 fallthrough。

### 1.4 指针、数组、字符串

- 数组不是指针，但数组名在大多数表达式中会 decay 成 `T*`，即首元素地址。
- `int a[N]` 退化后是 `int*`；`&a` 的类型是 `int (*)[N]`，是“指向整个数组的指针”。
- 函数参数里写 `int a[]`、`int a[10]`、`int *a` 本质上都一样，参数类型都是 `int*`。
- 在函数参数里对数组写 `sizeof(a)`，得到的是指针大小，不是数组长度。
- 【习题课补充】`void *` 可以表示“任意对象指针”；`malloc` 的返回值就是 `void *`，在 C 里接收它通常不需要显式转换。
- 【习题课补充】二维数组 `T[N][M]` 传参后会退化成 `T (*)[M]`，不是 `T **`。
- 【习题课补充】不同对象类型的指针即使数值地址相同，类型也不同；用错误类型的指针解引用通常是 `UB`。
- 指针加减整数按元素大小移动。
- `a + N` 是 one-past-the-end，允许存在但不能解引用。
- `a - 1`、越过 one-past 继续走、或不同数组之间做减法，都是 `UB`。
- 指针减法只对同一数组内（含 one-past）有意义，结果类型是 `ptrdiff_t`。
- `const` 分两层：低层 `const` 是“内容不可改”，高层 `const` 是“指针本身不可改”。
- 通过非 `const` 途径修改真正的 `const` 对象是 `UB`。
- C 中字符串字面量类型是 `char[N+1]`，但修改它是 `UB`；C++ 中字符串字面量类型是 `const char[N+1]`。
- 字符串以 `\0` 结尾。
- 【习题课补充】`strlen` 不计末尾 `\0`；`sizeof(array)` 看到的是整个数组占用的字节数。
- 常见字符串/字符函数：`strlen`、`strcpy`、`strcat`、`strchr`、`strcmp`、`isalpha`、`tolower`、`toupper`。
- 动态分配：`malloc` / `calloc` / `free`。
- 【习题课补充】`malloc` 只分配，不初始化，失败返回 `NULL`。
- 【习题课补充】`calloc` 会把分配到的字节清零。
- 【习题课补充】`free(NULL)` 安全；`free` 后原指针变成悬空指针，最好手动置空。
- 【习题课补充】`free` 只能接收原始分配指针或 `NULL`；`free(p + 1)`、重复 `free`、或释放后继续解引用都是 `UB`。
- 多层分配要逐层释放，别漏掉内层指针。

### 1.5 `struct`

- 语法：`struct Name { members; };`
- 访问：对象用 `.`，指针用 `->`。
- `.` 的优先级高于 `*`。
- `sizeof(struct)` 可能大于成员大小之和，因为有对齐填充。
- 初始化可用 `{...}`，也可用 designator：`{.member = value}`。
- `struct` 的赋值/传参/返回是逐成员复制。
  - 数组成员会逐元素复制。
  - 指针成员只复制指针值，不复制所指资源。
- 【习题课补充】C 里常用 `typedef struct { ... } Name;` 起别名，这样后面直接写 `Name x;` 即可。
- 若整个对象没有 initializer：全局 / 静态对象零初始化；局部自动对象成员值不确定；`malloc` 出来的内存默认不初始化。
- 若使用 initializer list 但省略部分成员，省略成员会按规则递归初始化。

### 1.6 `enum` / bitfield / `union`

- 【习题课补充】`enum` 是一组有名字的整型常量，适合代替 magic numbers；`enum` item 可以直接放进 `switch` 的 `case`。
- 【习题课补充】bitfield 的布局和大小是 implementation-dependent 的，别拿它做依赖具体字节布局的移植代码。
- 【习题课补充】`union` 的成员共用同一片存储，大小至少为最大成员大小；读取哪个成员要特别小心。

---

## 2. C++ 基础

### 2.1 IO 与 `std::string`

- `std::cin` / `std::cout` 是对象，不是函数。
- 输入用 `>>`，输出用 `<<`。
- `std::cin >> x` 会按类型自动读取，不需要手写 `&x`。
- 【习题课补充】`std::ifstream` / `std::ofstream` / `std::fstream` 定义在 `<fstream>`；文件流对象析构时会自动关闭文件。
- 【习题课补充】`std::istringstream` / `std::ostringstream` / `std::stringstream` 定义在 `<sstream>`，可把 `std::string` 当输入源或输出目标。
- `std::string` 常用：`+`、`+=`、`size()`、`empty()`、`begin()`、`end()`。
- `std::string` 没有 `-=`。
- `std::string` 还有 `reserve()`、`capacity()`、`shrink_to_fit()`。
- `std::getline(cin, s)` 读整行，会把换行符吃掉但不存进字符串。
- `std::string` 默认构造得到空串。
- `std::string` 的 `+` 左结合，`+=` 通常比 `s1 = s1 + s2` 更省临时对象。
- 【习题课补充】`std::to_string`、`std::stoi` / `stol` / `stoll` 等常用于数字与字符串互转。
- 【习题课补充】C++ 标准库名字都在 `std` 里；C 头文件在 C++ 中通常写成 `<cxxx>`，例如 `<cstdio>`。
- 【习题课补充】`std::endl` 会输出换行并刷新缓冲区。
- C++ 里 `nullptr` 优先于 `NULL`，更不容易和整数重载混淆；`NULL` 可能触发整数重载陷阱。

### 2.2 引用与值类别

- 引用本质上是别名，不是对象。
- 引用必须在定义时初始化，之后不能重新绑定。
- 没有“引用的引用”。`int &ri2 = ri;` 只是继续绑定到原对象。
- `const T &` 可以绑定临时对象，并延长生命周期。
- `T&&` 绑定右值；命名的 `T&&` 变量本身是左值。
- `std::move(x)` 只是把 `x` 转成可当作右值的形式，本身不移动任何东西。
- 被 move 过的对象仍然有效，但值通常不再可依赖，常只适合再赋值或析构。
- 【习题课补充】在基于范围的 `for` 里，`auto x` 会拷贝元素，`auto &x` 才会修改原元素，`const auto &x` 则只读且避免拷贝。
- 【习题课补充】引用也可以绑定数组，例如 `int (&r)[10] = a;`，这时它绑定的是整个数组而不是首元素指针。

### 2.3 类型推导与转换

- `auto x = expr` 会推导类型，通常丢掉顶层 `const` 和引用。
- `auto &x`、`const auto &x` 常用于避免拷贝。
- `decltype(expr)` 在编译期获取表达式类型。
- `CTAD` 是类模板实参推导，C++17 才有。
- 【习题课补充】`std::pair p{a, b};` 这类写法在 C++17 可通过 CTAD 推导模板参数；`pair` 成员是 `.first`、`.second`。
- 【习题课补充】结构化绑定：`auto [x, y] = pair_or_struct;`；遍历 `map` 时常写 `for (const auto &[k, v] : m)`。
- `static_cast<T>(expr)`：显式、相对安全的转换，但窄化/方向错误仍可能出事。
- `const_cast`：去掉低层 `const`；如果原对象本来就是 `const`，修改它是 `UB`。
- `reinterpret_cast`：最危险，通常只用于非常底层的指针/位级转换。
- `explicit` 可用于构造函数和转换函数，阻止隐式转换。
- `explicit` 的 `bool` 转换仍可在 `if`、`&&`、`||`、`?:` 里使用。
- 【习题课补充】`auto s = "hello";` 通常推成 `const char *`，不是字符串对象。
- 【习题课补充】`decltype(expr)` 不会真的求值 `expr`。

### 2.4 函数

- 形参默认值必须从右往左连续出现。
- 函数重载更偏好：精确匹配 > promotion > 一般转换 > 类转换。
- 数组参数会 decay，所以数组长度通常不会参与函数重载区分。
- 低层 `const` 会影响重载匹配；按值形参的顶层 `const` 不能构成不同重载。

### 2.5 类与特殊成员

- `class` 默认私有，`struct` 默认公有。
- `this` 指向当前对象；在 `const` 成员函数里，`this` 是 `const X*`。
- `const` 成员函数中 `this` 是 `const X*`，不能修改非 `mutable` 成员，可被 `const` 对象调用。
- 构造函数的初始化列表先于函数体执行。
- 成员初始化顺序按声明顺序，不按初始化列表书写顺序。
- 析构函数体执行完后，成员按声明顺序逆序销毁。
- 默认构造函数是“空参数列表”的构造函数。
- 如果类没有用户声明构造函数，编译器会尝试合成默认构造函数。
- 如果某个成员不能默认初始化，合成默认构造函数会被删除 / 不可用，使用时报 `CE`。
- 如果类已经有用户声明构造函数，编译器不会再自动合成默认构造函数。
- `T var;` 才是对象定义；`T var();` 会被解析成函数声明。
- `=default` 可以要求编译器合成特殊成员；`=delete` 可以禁用它。
- copy ctor: `T(const T&)`。
- copy assignment: `T& operator=(const T&)`。
- move ctor: `T(T&&)`。
- move assignment: `T& operator=(T&&)`。
- `copy/move assignment` 一般都要 `self-assignment safe`。
- 资源类通常要一起考虑 copy ctor、copy assignment、move ctor、move assignment、destructor。
- 现代 C++ 常说：要么定义 0 个，要么认真处理 5 个。
- 如果类里有资源，默认的浅拷贝经常不对。
- 【习题课补充】若用户声明了析构 / copy 等，编译器通常不会再隐式生成 move ctor / move assignment。
- 【习题课补充】deleted function 仍参加重载决议；一旦被选中就是 `CE`。
- 【习题课补充】默认移动行为近似对成员逐个 `std::move`，能移动就移动，不能移动时可能退化为拷贝或被删除。
- 【习题课补充】构造函数常用“pass-by-value then move”：参数按值接收，再 `std::move` 到成员里，让左值拷贝、右值移动。
- 【习题课补充】移动构造 / 移动赋值通常写 `noexcept`，容器搬家时会更愿意使用 move。
- 【习题课补充】快速 `swap` 常用于实现异常安全的赋值；`operator=(T other)` 可统一 copy/move assignment。
- 【习题课补充】类内初始值（in-class initializer）会在构造时作为默认值使用，除非构造函数初始化列表里另行指定。
- 【习题课补充】`const` 成员和引用成员必须在初始化列表里初始化。
- 【习题课补充】析构函数函数体结束后，编译器会自动销毁成员对象。
- 【习题课补充】C++ 里要配对使用 `new` / `delete`、`new[]` / `delete[]`；例如动态数组通常是 `new T[n]` 配 `delete[]`。
- 【习题课补充】写拥有资源的类时，常见模式是构造函数分配、析构函数释放，必要时再补拷贝/移动控制成员。

### 2.6 静态成员与 friend

- `static` 成员属于类本身，所有对象共享。
- `static` 成员函数没有 `this`，只能直接访问静态成员。
- 类外访问静态成员用 `ClassName::name`。
- `friend` 不是成员，只是授予访问权限的声明。
- `friend` 声明可以放在类体里的任意位置，访问控制关键字对它不起作用。
- `using Name = Type;` 是推荐的类型别名写法。

### 2.7 运算符重载与类型转换

- 运算符重载至少要有一个类类型操作数。
- 不能改变运算符的优先级、结合性、参数个数，也不能创造新运算符。
- 【习题课补充】不能重载 `.`, `::`, `?:`, `.*`；不建议重载 `&&` / `||`，因为短路求值会失效。
- 二元运算符通常写成 non-member；如果要访问 private 成员，常配合 `friend`。
- `<<` / `>>` 的重载通常返回 `ostream&` / `istream&`，便于链式调用。
- `++x` 通常返回 `T&`；`x++` 通常返回旧值副本。
- `operator()` 是函数调用运算符，仿函数 / lambda 都靠它表现得像函数。
- 用户定义类型转换可以通过构造函数或转换运算符实现。
- 转换运算符通常写成 `operator T() const`。
- `explicit` 可阻止隐式类型转换。
- `explicit operator bool()` 仍可用于 `if`、`&&`、`||`、`?:` 这类布尔上下文。
- 【习题课补充】后置 `++` / `--` 通常写成 `operator++(int)` / `operator--(int)`，那个 `int` 只是用来区分前置版本。
- 【习题课补充】`operator->` 通常要返回指针，使 `p->mem` 和 `(*p).mem` 保持一致。
- 【习题课补充】输入 / 输出运算符必须是非成员，才能让流对象出现在左边。

---

## 3. STL

### 3.1 总览

- STL 主要包括：containers、iterators、algorithms、function objects、adaptors、allocators。
- 考试里最常见的是：读代码、判断 iterator 失效、判断 `set/map` 行为、判断 `unique_ptr/shared_ptr` 所有权。

### 3.2 Smart Pointers

| 类型 | 所有权 | 复制 | 常见写法 | 备注 |
|---|---|---|---|---|
| `std::unique_ptr<T>` | 独占 | 不可复制，只能 move | `std::make_unique<T>(...)` | move 表示所有权转移 |
| `std::shared_ptr<T>` | 共享 | copy 会共享所有权 | `std::make_shared<T>(...)` | 引用计数；环引用会泄漏 |

- smart pointer 默认都可以是空指针。
- `operator bool` 可用于 `if (p)`，判断是否非空。
- `get()` 返回原始指针，只是“观察者”，不负责释放。
- `unique_ptr` 适合独占资源管理；数组版是 `std::unique_ptr<T[]>`，但大多数动态数组更适合 `std::vector<T>`。
- 【习题课补充】`unique_ptr<T>` 管 `new T[n]` 会用错删除形式；动态数组要用 `unique_ptr<T[]>` 或直接用 `vector<T>`。
- 【习题课补充】`release()` 放弃所有权并返回裸指针，调用者必须负责释放；`reset()` 释放或替换当前对象。
- `make_unique` / `make_shared` 一般优先于直接写 `new`。
- `shared_ptr` copy 时引用计数加 1；销毁或 reset 时减 1，减到 0 才销毁对象。
- `shared_ptr` move 只是转移句柄，源对象变空，不是“重新计数”。
- `shared_ptr` 解决不了环引用；双向链表这类场景要小心。
- `weak_ptr` 这门课不展开。

### 3.3 Iterators

- 迭代器是“泛化的指针”，统一访问不同容器元素。
- `std::begin(c)` / `std::end(c)`：容器返回 `c.begin()` / `c.end()`；数组返回 `a` / `a + N`。
- `end()` 是 off-the-end，不能解引用。
- `++it` 前进到下一位置；最后一个元素的 iterator `++` 后得到 `end()`，但对 `end()` 再 `++` 是 `UB`。
- 原始指针本身就是 random access iterator。
- 【习题课补充】`const` 容器上通常应使用 `const_iterator`；`cbegin()` / `cend()` 也会返回只读迭代器。
- 【习题课补充】`std::advance(it, n)` 改变 `it`；`std::next(it)` / `std::prev(it)` 返回新迭代器；`std::distance(first, last)` 返回距离。

| 类别 | 支持 |
|---|---|
| `ForwardIterator` | `*`、`->`、`++`、`==`、`!=` |
| `BidirectionalIterator` | 上面再加 `--` |
| `RandomAccessIterator` | 上面再加 `+n`、`-n`、`[]`、距离、比较大小 |

- `vector` 重新分配时，旧的 iterator / reference / pointer 可能全部失效。
- `push_back` 循环里最容易踩 iterator invalidation。
- range-for 等价于 iterator 遍历。
  - `auto x : c` 会拷贝。
  - `auto &x : c` 可修改原元素。
  - `const auto &x : c` 只读且避免拷贝。

### 3.4 Algorithms

- STL algorithms 接受的是 iterator range：`[begin, end)`。
- 普通算法本身不会改变容器长度；传 `back_inserter` 这类 iterator adaptor 时例外。
- `_n` 版本表示“起点 + 个数”，例如 `copy_n`、`fill_n`。
- `std::copy` 只是复制，不会插入；输出区必须已经有足够空间。
- `std::unique` 只去掉相邻重复，不改变容器长度，只返回新逻辑尾；常配合 `erase` 使用。
- `std::find` 找不到时返回 `end()`。
- `std::sort` 需要 `RandomAccessIterator`。
- `std::lower_bound`、`std::upper_bound`、`std::binary_search` 需要有序范围。
- `std::accumulate(begin, end, init)` 的返回类型受 `init` 影响。
- `std::sort(begin, end, cmp)` 里的 `cmp` 是 callable：函数、函数指针、仿函数、lambda 都行。
- `cmp(a, b)` 应该表示 `a` 排在 `b` 前面；必须形成严格弱序，别写 `<=`。
- 【习题课补充】`std::back_inserter(c)` 会把赋值转化为 `c.push_back(x)`，适合给空容器做 `copy` 输出。

常见算法：

- 非修改：`count`、`find`、`find_end`、`find_first_of`、`search`
- 修改：`copy`、`fill`、`reverse`、`unique`
- 排序/区间：`partition`、`sort`、`stable_sort`、`nth_element`、`merge`、`inplace_merge`
- 二分：`lower_bound`、`upper_bound`、`binary_search`、`equal_range`
- 堆：`is_heap`、`make_heap`、`push_heap`、`pop_heap`、`sort_heap`
- 其他：`min_element`、`max_element`、`minmax_element`、`equal`、`lexicographical_compare`、`accumulate`、`inner_product`

### 3.5 Containers

- `std::string` 不是课上重点意义上的 container，但行为很像 sequence container。
- `std::array<T, N>` 是固定大小容器，不会 decay 成 `T*`。
- 【习题课补充】常见容器构造形式有：`Container c`、`Container c(n, x)`、`Container c(n)`、`Container c(begin, end)`；`array<T, N>` 只支持固定大小那种。
- 【习题课补充】`string` 和 `vector` 的 `reserve(n)` 只改容量不改大小，`resize(n)` 会真的改变元素个数。

| 容器 | 特点 |
|---|---|
| `std::vector<T>` | 连续动态数组；随机访问；尾部插入快；中间插删慢 |
| `std::deque<T>` | 头尾插删快；也支持随机访问；中间插删慢 |
| `std::list<T>` | 双向链表；可双向遍历；没有随机访问 |
| `std::forward_list<T>` | 单向链表；只支持前向遍历 |
| `std::array<T, N>` | 固定大小；像普通数组但有容器接口 |

- 常见接口：`at`、`[]`、`front`、`back`、`begin`、`end`、`size`、`empty`。
- `at()` 会做边界检查，越界抛 `std::out_of_range`。
- `[]` 不检查边界。
- `front()` / `back()` / `pop_back()` / `pop_front()` 在空容器上不安全。
- `resize(n)`：新元素 value-initialize。
- `resize(n, x)`：新元素复制 `x`。
- `capacity()` / `reserve()` 主要用于 `string` 和 `vector`；`shrink_to_fit()` 是释放多余容量的请求，不保证一定收缩。
- `push_back`、`emplace_back`、`pop_back` 主要针对尾部。
- `push_front`、`emplace_front`、`pop_front` 主要针对头部。
- `insert`、`emplace`、`erase` 负责指定位置操作。
- `vector` / `string` / `deque` 的中间插删通常是 `O(n)`。
- 容器适配器：`stack`、`queue`、`priority_queue`，它们不是容器本身。
- 【习题课补充】`emplace_*` 会把参数原地构造成元素，避免先构造再拷贝 / 移动。
- 【习题课补充】`forward_list` 更轻量，但不支持 `size()`、`push_back()`、`pop_back()`；它用 `insert_after` / `erase_after` 操作链表。
- 【习题课补充】`insert(pos, ...)` 和 `emplace(pos, ...)` 都是在 `pos` 之前插入。

### 3.6 Associative Containers

- 关联容器分为 ordered 和 unordered 两类。
- ordered：`set`、`map`、`multiset`、`multimap`，通常基于红黑树，操作大多是 `O(log n)`。
- unordered：`unordered_set`、`unordered_map`、`unordered_multiset`、`unordered_multimap`，通常基于哈希表，平均 `O(1)`。
- ordered 需要严格弱序比较器，默认用 `std::less` / `operator<`；unordered 需要 hash 和 equality。

#### `std::set`

- 元素有序、无重复。
- `set` / `map` 的单元素 `insert` / `emplace` 常返回 `pair<iterator, bool>`；`multi*` 容器允许重复，返回形式不同。
- `erase(key)` 返回删除个数，通常是 `0` 或 `1`。
- `find(x)` 找到返回迭代器，找不到返回 `end()`。
- 迭代器是 bidirectional。
- 通过迭代器拿到的元素不能直接改。
- `multiset` 允许重复元素。

#### `std::map`

- 存的是 key-value 对。
- 元素类型是 `std::pair<const Key, Value>`。
- key 有序且不能直接改；value 可以改。
- `m[key]`：如果 key 不存在，会先插入 `{key, Value{}}`，再返回 value 的引用。
- `find(key)` 不会插入。
- `count(key)` 常用于判断是否存在。
- 遍历时常写：`for (const auto &[k, v] : m)`；若要改 value，可写 `for (auto &[k, v] : m)`，但 `k` 仍不能改。
- `multimap` 允许重复 key。

#### 速记

- `set` / `map`：有序、树、`O(log n)`。
- `unordered_set` / `unordered_map`：无序、哈希、平均 `O(1)`。
- `set` 里看“值”；`map` 里看“键值对”。
- `map[key]` 可能改动容器，`find` 不会。
