1. It works just like std::mutex, except that you can acquire multiple locks on a single instance from the same thread -- it locks on thread level, one thread can lock the recursive_mutex multiple times.
3. You must release all your locks before the mutex can be locked by another thread, so if you call lock() three times, you must also call unlock() three times.
4. Must be very carefully used, it's a dangerous thing just like recursion method itself -- we don't use recursion a lot.
```cpp
// the code snippet will only print 1, 2 then 3, 4 or 3, 4 then 1, 2
recursive_mutex mtx;
void test1() {
    mtx.lock();
    cout << "test1: 1" << endl;
    mtx.lock();
    cout << "test1: 2" << endl;
    mtx.unlock();
    mtx.unlock();
}
void test2() {
    mtx.lock();
    cout << "test2: 3" << endl;
    mtx.lock();
    cout << "test2: 4" << endl;
    mtx.unlock();
    mtx.unlock();
}
int main() {
    thread t1(test1);
    thread t2(test2);
    t1.join();
    t2.join();
    return 0;
}
```
3. Correct use of std::lock_guard<std::recursive_mutex> and std::unique_lock<std::recursive_mutex> will handle the unlock for you.
```cpp
// equivalent as above(can replace unique_lock with lock_guard)
recursive_mutex mtx;
void test1() {
    unique_lock<recursive_mutex> lk(mtx);
    cout << "test1: 1" << endl;
    unique_lock<recursive_mutex> lk2(mtx);
    cout << "test1: 2" << endl;
}
void test2() {
    unique_lock<recursive_mutex> lk(mtx);
    cout << "test2: 3" << endl;
    unique_lock<recursive_mutex> lk2(mtx);
    cout << "test2: 4" << endl;
}
int main() {
    thread t1(test1);
    thread t2(test2);
    t1.join();
    t2.join();
    return 0;
}

// a real example of using the lock in recursion
int depth1 = 0; // depth is used to control the stop point of recursion, in real world if you are dfs a tree then the end will be after visiting of the leaf node
int depth2 = 0; 
recursive_mutex mtx;
void dfs1() {
    unique_lock<recursive_mutex> lk(mtx);
    depth1++;
    cout << depth1 << " th time to call dfs1" << endl;
    if (depth1 == 3) {
        return;
    }
    dfs1();
}
void dfs2() {
    unique_lock<recursive_mutex> lk(mtx);
    depth2++;
    cout << depth2 << " th time to call dfs2" << endl;
    if (depth2 == 3) {
        return;
    }
    dfs2();
}
int main() {
    thread t1(dfs1);
    thread t2(dfs2);
    t1.join();
    t2.join();
    return 0;
}
```
