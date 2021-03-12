#### transform()
```cpp
int square(int elem)
{
    return elem * elem;
}
...
transform(coll.cbegin(), coll.cend(), coll.begin(), square);
```

#### for_each()
```cpp
void square(int& elem)
{
    elem = elem * elem;
}
...
for_each(coll.begin(), coll.end(), square);
```

#### static
1. static variable in functions
initialized only once, and then hold there value thorugh function calls.
a static variable inside a function keeps its value between invocations.
static variables are stored on static storage area, not in stack.
```cpp
int counter() {
static int count=0;
return count++;
}
```

2. static class objects
object declared static are allocated in static storage area, and have scope till the end of program.
static object initalized using constructors. assignment to zero is only for primitive datatypes, not for user-defined datatypes.
```cpp
class Abc {
int i;
Abc() { i=0; }
~Abc() {}
};

void f() {
static Abc obj;
}

int main() {
f();
// destructor ~Abc() not called yet
// ...
}
```

3. static member variable in class
static data members are shared by all the objects. it has a single piece of storage, and is not available as separate copy with each object. 
itialized not from constructor/object inialization.
must be inialized explicitly outside the class. linker error if not initalized.
```cpp
class X {
public:
static int i;
};

int X::i=1;

int main() {
X obj;
}
```

4. static member methods in class
static member class functions could be used w/o an object of the class.
these functions cannot access non-static data members, but only static members and static member functions.
```cpp
class X {
public:
static void f() {
// ...
}
};

int main() {
X::f(); // calling static member function directly with class name
}
```
5. Static global variables or functions
are "seen" only in the file it's declared in

#### std::variant<>
```cpp
std::variant<int, std::string> var{"hi"};
std::cout << var.index() << '\n'; // prints 1
var = 42;
std::cout << var.index() << '\n'; // prints 0
```
#### allocators \<memory\>


#### remove_if


#### variadic templates
template that accept a variable number of template arguments
```
void print()
{
}

template<typename T, typename... Types>
void print (const T& firstArg, const Types&... args)
{
    std::cout<<firstArg << std::endl;
    print(args...);
}
```  

#### constexpr  
enable expression evaluated at compile time
```
constexpr int square(int x)
{
    return x * x;
}
float a[square(9)]; // OK since c++11: a has 81 elements
```

#### unique_ptr
```void reset()```
replaces managed object
```pointer release() noexecpt;```
releases the ownership of the managed object
any get() returns nullptr after the call

#### scoped enum
```
enum class Note : char { C, D, E, F, G, A, B };
```

#### auto type deduction  
```
auto i = 42; // i has type int
double f();
auto d = f(); // d has type double
```

#### nullptr_t  
helps to avoid mistakes when a null pointer was interpreted as integral value  

```
void f(int);
void f(void*);

f(0); // calls f(int)
f(NULL); // calls f(int) if NULL is 0
f(nullptr); // calls f(void*)
```

#### unique_ptr  
owns and manages objects through pointer  
dispose that object when unique_ptr goes out of scope  
