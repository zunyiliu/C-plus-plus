### Definition
1. Flexible Locking and Unlocking: allows for flexible management, including deferred locking, manual locking, and unlocking, and transferring lock ownership.
2. Support lock/unlock multiple times.
3. Support for Condition Variables.
4. Moveable but Not Copyable.
#### Usage
```cpp
void function() {
    unique_lock<mutex> lk(mtx1); // by default the mtx is locked, unless 2nd argument is defined like defer_lock etc
    do_somthing();
    lk.unlock(); // still need to manually unlock and lock if several lock/unlock actions are required within the scoped function
    lk.lock();
    do_other_thing();
    // don't need manually unlock since lk is scoped within the function, when function ends all resources within the function(by calling destructor) will be destroyed in reverse order
    // and in destructor the unique_lock helps us to unlock mutex automatically
}
```
#### compare with lock_guard
1. lock_guard is also unique, however, it is locked automatically when it's created, it can't be lock/unlock manually.
2. lock_guard is for simple use case, it's slightly faster than unique_lock, unique_lock is used when the scenario is more complex and need more control. 
```cpp
lock(mtx1, mtx2);
lock_guard<mutex> lg1(mtx1, std::adopt_lock); // can have adopt_lock to inform the lock has already locked, but there's no defer_lock for lock_guard
lock_guard<mutex> lg2(mtx2, std::adopt_lock);

// this is equivalent as above, and defer_lock is to ask unique_lock not lock mutex for now
unique_lock<mutex> lock_a(mtx1, std::defer_lock);
unique_lock<mutex> lock_b(mtx2, std::defer_lock);
lock(lock_a, lock_b);
```

### FAQ
What is move?  
a source is an lvalue--a real variable or reference to one or an rvalue--a temporary of some kind. Ownership transfer is automatic if the source is an rvalue and must be done explicitly(using std::move()) for an lvalue in order to avoid accidentally transferring ownership away from a variable.
```cpp
unique_lock<mutex> get_lock() {
    mutex sm;
    unique_lock<mutex> lk(sm);
    return lk;
}

int main() {
    // this can compile as uq must be passed as rvalue, the uq is transferred to lk
    unique_lock<mutex> uq = get_lock();
    unique_lock<mutex> lk(move(uq));

    // this also works because the returned unique_lock is an automatic variable declared in the function
    // no need to move as there's no reference of the returned lock
    unique_lock<mutex> lk(get_lock());

    // this is wrong as unique lock is not copiable
    unique_lock<mutex> uq = get_lock();
    unique_lock<mutex> lk(uq);
    return 0;
}
```
