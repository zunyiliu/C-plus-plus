### Format
```cpp
// this has compile error if the compiler version is not correct
[capture_clause] (parameters) -> return_type {
    function_body
}
or simplified as
[capture_clause] (parameters) {
    function_body
}
```
1. capture_clause: Specifies which variables from the surrounding scope are available inside the lambda and how (by value, by reference). It can be empty.
2. parameters: params of the function
3. function_body: lambda function body
### Example
```cpp
int x = 10, y = 10;
// (param) can be ignored
// [x, y] means x and y are passed by value (copied when pass to lambda)
auto add = [x, y] {
    return x + y;
}
// to call add
int v = add();

// another example with params
auto multiply = [](int a, int b) {
    return a * b;
};
cout << multiply(3, 5) << endl;

// another example, for_each is defined in <algorithm>
vector<int> v = {1, 2, 3, 4, 5};
int sum = 0;
std::for_each(v.begin(), v.end(), [&sum](int n) { // [&sum] means sum is passed by reference
    sum += n;
});
cout << sum << endl; // will print 15
```
