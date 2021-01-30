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
