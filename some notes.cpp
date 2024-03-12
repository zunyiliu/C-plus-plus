// 1. & and * operator
int num = 3; // declare a int variable num and assign 3 to it
int* p = &num; // int*: declare this is a int pointer, &num: & is used as Address-of Operator, the address of num
int** pp = &p; // int**: pointer of pointer, &p: address of pointer p
int &num1 = num; // declare as a reference, now num1 and num points to the value in same address, num1 = 3 will change num to 3 as weel
int* p1 = p; // same, copy the val of p and assign it to p1: &p1 and &p will be different
int* &p2 = p; // &p2 will == &p, the address of two pointers are the same, p2 is just an alias of p

// 2. param in method
method(int& num){} // pass by reference, change num will change the orignial variable that passed into method
method(int num){} // pass by value, the param is just a copy of the original variable -- 这里有个很大的不同，java之类的语言如果传的是一个对象或者数组/list，传过去的是一个reference，而在C++里是会把整个对象/数组拷贝以后以值的方式传入的
method(int* num){} // pass by reference

// 3. usage of a pointer 
// Obj* p: p -> val, or (*p).val
// vector<int>* p: p -> at(x) or (*p)[x]

// 4. unordered_set(hashSet equivalent in Java)
unordered_set<string> set;
set.insert("code"); // add
set.erase("code"); // remove, won't throw error if not found
set.find(key) == set.end(); // contains, set.find(key) returns an iterator of the key, if key not found then return set.end()
unordered_set<string>::iterator itr = set.find(key); 
int val = *itr; // use * to access value of iterator, iterator is an abstract type which can have similar operation like a pointer
unordered_set<string>::iterator begin = set.begin();
begin++; // use ++ for itr to move backwards
// note: iterator operation is depending on the type, for an unordered_set, you can only apply ++ to move backwards, some can accept -- to move forward and some can accept itr += n for random access
unordered_set<string>::iterator end = set.end();
set.clear(); // clear set


// 5. unordered_map<int, int> map (hashmap equivalent in Java)
// add key-val pair, both works
map.insert(std::make_pair(2, 1));
map[2] = 1;
// iterate the map, auto is similar like var in Java
// auto is std::pair<const KeyType, ValueType>& here
for (auto x : map) {
    cout << x.first << " " << x.second << endl;
}
// auto is iterator here, std::map<KeyType, ValueType>::const_iterator, must use -> to access first/second data
auto x = map.find(3);
cout << x -> first << " " << x -> second << endl;
// note: use map.find(key) == map.end() to check if a key exists in the map, map[key] == val will automatically insert a default val to the key if the key doesn't exist in the map
map.clear();
map.erase(key);

// 6. array
bool f[10] = {}; // init an array with size ten and value to default
bool f[10] = {true}; // init and set f[0] to true, others are set as default
bool f[10]; // the values of the array are not defined, have to set value before accessing them, e.g. cout << f[0] << endl will throw an error
// note that bool f[x] = {} is not acceptable as c++ doesn't support variable-sized array, use vector<bool> vec(false,x) instead

// 7. vector
vector<int> vec; // init an empty vector
vecotr<int> vec(10,-1); // init a vector with size to 10 and set default values to -1
vec.push_back(); // creates a copy of the object and append at the end of vector
sort(vec.begin(), vec.end(), [](const vector<int>& a, const vector<int>& b) { // sorting
    return a[0] < b[0];
});
// [] meaning: Capture Clause in Lambda
[] means that no variables are captured from the enclosing scope. The lambda cannot use variables from outside its own scope.
[x, y] captures variables x and y by value, making a copy for the lambda to use.
[&x, &y] captures variables x and y by reference, allowing the lambda to modify the original variables.
[=] captures all automatic (local) variables used in the lambda by value.
[&] captures all automatic (local) variables used in the lambda by reference.
[&, x] captures variables by reference by default, but captures variable x by value.
[=, &x] captures variables by value by default, but captures variable x by reference.

// 8. priority_queue -> has a reverse way in comparator vs Java(or sort in c++)
priority_queue<int> pq; // max heap
priority_queue<int, std::vector<int>, std::greater<int>> pq; // min heap
struct CompareStudent {
    bool operator()(const Student& a, const Student& b) {
        return a.gpa < b.gpa; // change to > for ascending order
    }
};
priority_queue<Student, std::vector<Student>, CompareStudent> pq; // pq with comparator
pq.push(); pq.pop(); pq.top();pq.empty();

// 9. map -> treemap in Java
map<int, std::string> map;
map.insert(std::make_pair(1, "One"));
map.erase(1);
map.find() == map.end();
struct MyComparator {
    bool operator()(const MyClass& a, const MyClass& b) const {
        return a.value < b.value;
    }
};
map<MyClass, std::string, MyComparator> myMap;
// 10. set -> treeset in Java
set<int> set;
set<int, ReverseComparator> mySet;
struct ReverseComparator {
    bool operator()(const int& lhs, const int& rhs) const {
        return lhs > rhs; // reverse order
    }
};

// 10. list, linkedlist in java


// 11. deque,  

// dangling reference
Class *object = new Class();
Class *object2 = object;
delete object;
object = nullptr; // now object2 points to something which is not valid anymore

Object *method() {
  Object object;
  return &object;
}
Object *object2 = method(); // object2 points to an object which has been removed from stack after exiting the function

// wild pointer
int* p; /* wild pointer */
int a = 10;
/* p is not a wild pointer now*/
p = &a;
/* This is fine. Value of a is changed */
*p = 12;

// pass anonymous function as param
class X {
public:
    // function<x(y)> z, x is the return type, y is the param, z is the name of the function
    void test(function<void(int)> func) {
        func(1);
    }
};
// to call the function
auto f = [](int x) {
    std::cout << x << endl;
};
X x;
x.test(f);
