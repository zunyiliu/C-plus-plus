```cpp
lock(mtx1, mtx2);
lock_guard<mutex> lg1(mtx1, std::adopt_lock);
lock_guard<mutex> lg2(mtx2, std::adopt_lock);

// this is equivalent as above, and defer_lock is to ask unique_lock not lock mutex for now
unique_lock<mutex> lock_a(mtx1, std::defer_lock);
unique_lock<mutex> lock_b(mtx2, std::defer_lock);
lock(lock_a, lock_b);
```
