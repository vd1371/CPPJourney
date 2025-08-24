# Quiz: Phase 1, Step 2 - Modern C++ Fundamentals

**Instructions**: Answer the following questions to test your understanding of modern C++ features. This quiz covers C++11/14 core features, modern initialization, lambda expressions, and smart pointers.

## Questions

### 1. Type Deduction and `auto`
What is the type of `result` in the following code?
```cpp
std::vector<double> prices{100.0, 150.0, 200.0};
auto result = prices.begin();
```

**Options:**
a) `std::vector<double>::iterator`
b) `std::vector<double>::const_iterator`
c) `double*`
d) `std::iterator<double>`

### 2. `decltype` Usage
What does the following code output?
```cpp
int x = 42;
decltype((x)) y = x;
y = 100;
std::cout << x;
```

**Options:**
a) 42
b) 100
c) Compilation error
d) Undefined behavior

### 3. Trailing Return Types
Which of the following is the correct syntax for a trailing return type in C++11?

**Options:**
a) `auto function() -> int { return 42; }`
b) `int function() -> auto { return 42; }`
c) `auto function() -> decltype(42) { return 42; }`
d) Both a and c

### 4. Uniform Initialization
Which of the following will cause a compilation error due to narrowing conversion?

**Options:**
a) `int x{42};`
b) `int y{3.14};`
c) `int z{static_cast<int>(3.14)};`
d) `int w = {42};`

### 5. Initializer Lists
What is the output of the following code?
```cpp
class Container {
public:
    Container(std::initializer_list<int> values) {
        for (auto val : values) {
            data_.push_back(val * 2);
        }
    }
    
    int get(int index) const { return data_[index]; }
    
private:
    std::vector<int> data_;
};

Container c{1, 2, 3};
std::cout << c.get(1);
```

**Options:**
a) 1
b) 2
c) 4
d) Compilation error

### 6. Lambda Capture Clauses
What is the output of the following code?
```cpp
int threshold = 100;
auto lambda = [threshold](int price) {
    return price > threshold;
};

threshold = 200;
std::cout << lambda(150);
```

**Options:**
a) true
b) false
c) Compilation error
d) Undefined behavior

### 7. Generic Lambdas (C++14)
Which of the following is a valid generic lambda expression?

**Options:**
a) `auto lambda = [](auto a, auto b) { return a + b; };`
b) `auto lambda = [](T a, T b) { return a + b; };`
c) `auto lambda = [](int a, int b) -> auto { return a + b; };`
d) `auto lambda = [](auto a, auto b) -> decltype(a + b) { return a + b; };`

### 8. Smart Pointer Ownership
What happens to `ptr1` after the following operation?
```cpp
auto ptr1 = std::make_unique<int>(42);
auto ptr2 = std::move(ptr1);
```

**Options:**
a) `ptr1` contains the value 42
b) `ptr1` is nullptr
c) `ptr1` points to the same memory as `ptr2`
d) Compilation error

### 9. Reference Counting
What is the reference count after the following operations?
```cpp
auto data = std::make_shared<std::string>("AAPL");
std::vector<std::shared_ptr<std::string>> container;
container.push_back(data);
container.push_back(data);
auto weak = std::weak_ptr<std::string>(data);
```

**Options:**
a) 1
b) 2
c) 3
d) 4

### 10. Lambda in Async Context
Which of the following lambda capture patterns is safe for use in a detached thread?

**Options:**
a) `[&localVar]() { /* use localVar */ }`
b) `[localVar]() { /* use localVar */ }`
c) `[=]() { /* use local variables */ }`
d) Both b and c

## Bonus Question (Advanced)

### 11. Perfect Forwarding with Lambdas
Consider the following code:
```cpp
template<typename F, typename... Args>
auto callWithPerfectForwarding(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

auto lambda = [](int x, double y) { return x + y; };
auto result = callWithPerfectForwarding(lambda, 10, 3.14);
```

What is the type of `result`?

**Options:**
a) `int`
b) `double`
c) `decltype(lambda(10, 3.14))`
d) Compilation error

---

**Note**: This quiz tests both theoretical understanding and practical application of modern C++ features. Review the step materials if you encounter difficulties with any questions.
