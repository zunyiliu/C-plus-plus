### condition_variable
1. std::condition_variable is specifically designed to work with std::mutex through std::unique_lock<std::mutex>.
2. It cannot directly work with other types of mutexes, such as std::shared_mutex. Why? shared_mutex is supposed to share among threads, and in condition_variable use case we are notifying one thread to do synchronization.
3. It can only work with unique_lock. Why? a. the waiting thread must unlock the mutex while it’s waiting and lock it again afterward(when notified). b. if the thread is notified and you have a large data process afterwards, you don't need to hold the lock until all things until data are processed, you can release the lock immediately by calling lk.unlock() explicitly.   
4. notify_one: only one thread will be waken, if multiple threads are waiting then one of them(not specified) will be waken, it's arbitrary and depends OS scheduling etc.
5. notify_all: all waiting threads will be waken up and then compete to acquire the mutex.  
6. examples
```cpp
// wait without predicate(the lambda function)
mutex mtx;
unique_lock<mutex> lk(mtx); // mtx is locked
condition.wait(lk);

// wait with predicate(the lambda function)
mutex mtx;
unique_lock<mutex> lk(mtx, []() {return !queue.empty()}); // mtx is locked
condition.wait(lk);
```
6. a practice consumer/producer model
```cpp
std::queue<some_data> q;
std::mutex mtx;
std::condition_variable condition;
void produce(int v) {
    lock_guard<mutex> lk(mtx);
    q.push(some_data(v));
    condition.notify_one();
}
void consume() {
    while (true) {
        unique_lock<mutex> lk(mtx);
        condition.wait(lk, []() {
            return !q.empty();
        });
        some_data data = q.front();
        q.pop();
        lk.unlock();
        // do_something();
    }
}
```
### Important!! how things actually work
1. std::unique_lock<std::mutex> lk(mtx); locks the mutex mtx.
2. cv.wait(lk, predicate); first evaluates the predicate:  
   If the predicate is true, it proceeds without waiting(mtx keeps locked).  
   If the predicate is false, it unlocks mtx and puts the current thread into a wait state.
   If there's no predicate, it's equivalent as predicate is false -> unlocks mtx and puts current thread to wait.  
4. When the condition variable is notified (through cv.notify_one() or cv.notify_all()), the waiting thread tries to get the mutex, if it's notify_all then all notified threads will wake and compete for the lock(by lock, we mean get the mutex and lock it), if it's notify_one then arbitrarily notify one of the waiting thread. 
5. Once the mutex is reacquired, the predicate is evaluated again:  
   If the predicate is now true, the wait operation completes, and the thread continues execution with the mutex locked.  
   If the predicate is false, the thread goes back into the wait state, and the mutex is unlocked again. This process repeats until the predicate returns true.
   If there's no predicate then no need to consider it, same as it's true
6. the preicate lambda function is executed safely as long as it's accessing data protected by the mutex, since the predicate is executed when the thread holds the lock, however there's possible to have a unsafe practice in real world that you are accessing unprotected data in predicate.
7. condition_variable states: initially for threads condition_variable is in wait state, when it's notified it will turn to ready state and trying to acquire mutex. So notify_all() will indeed wake up all threads but only one thread can acquire the lock, however all other threads are not waiting condition_variable anymore, they are blocked at getting lock. Unless a thread gets lock, checks predicate which returns false, then it will release the lock and go back to wait notify again.
8. condition_variable must use with the same lock over all threads, otherwise the behavior becomes unpredicatable.
#### Lambda that used in condition_variable
https://github.com/zunyiliu/C-plus-plus/blob/main/C%2B%2B%20concurrency%20in%20action/avoid%20deadlock.md
