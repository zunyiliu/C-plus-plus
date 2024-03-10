### lock_guard helps you to manage mutex so you don't need lock and unlock the mutex by yourself
```cpp
mutex mtx;
lock_guard<mutex> lg(mtx); // lock the mtx and manage the mtx to you

mtx.lock();
lock_guard<mutex> lg(mtx, std::adopt_lock); // inform lock_guard to just adopt the lock, but not lock it again
//e.g. when there are two mutex locked together, we want to manage them using lock_guard
lock(mtx1, mtx2);
lock_guard<mutex> lg1(mtx1, std::adopt_lock);
lock_guard<mutex> lg2(mtx2, std::adopt_lock);
```
