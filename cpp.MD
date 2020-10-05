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
helps to avoid mistages when a null pointer was interpreted as integral value  

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