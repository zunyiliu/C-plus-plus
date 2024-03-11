### condition_variable
1. std::condition_variable is specifically designed to work with std::mutex through std::unique_lock<std::mutex>. It cannot directly work with other types of mutexes, such as std::shared_mutex.
2. notify_one: only one thread will be waken, if multiple threads are waiting then one of them(not specified) will be waken.
3. notify_all: all waiting threads will be waken.
4. example of notify_one without predicate(the lambda function) and how things work.
```cpp
mutex mtx;
unique_lock<mutex> lk(mtx); // mtx is locked
condition.wait(lk); // thread blocks here and unlock the mtx, until it's notified and it will lock the mtx again then continue
```

### Important!! how things actually work
1. std::unique_lock<std::mutex> lk(mtx); locks the mutex mtx.
2. cv.wait(lk, predicate); first evaluates the predicate:  
   If the predicate is true, it proceeds without waiting.  
   If the predicate is false, it unlocks mtx and puts the current thread into a wait state.  
3. When the condition variable is notified (through cv.notify_one() or cv.notify_all()), the waiting thread is unblocked, but before it actually wakes up, the wait function internally reacquires the mutex mtx.
4. Once the mutex is reacquired, the predicate is evaluated again:  
   If the predicate is now true, the wait operation completes, and the thread continues execution with the mutex mtx locked.  
   If the predicate is false, the thread goes back into the wait state, and the mutex is unlocked again. This process repeats until the predicate returns true.  
#### Lambda that used in condition_variable
https://github.com/zunyiliu/C-plus-plus/blob/main/C%2B%2B%20concurrency%20in%20action/avoid%20deadlock.md
