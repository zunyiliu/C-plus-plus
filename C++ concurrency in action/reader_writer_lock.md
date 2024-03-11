1. what is that? read threads can concurrently access the resource, while read/write or write/write threads can't.
2. use case? read heavy but write light, e.g. DNS resolving domain names, the data will be read a lot but rarely write.
3. shared_mutex: a shared mutex, multiple shared_lock can lock the mutex without waiting each other, this can only be called by shared_mtx.lock_shared() or using
   shared_lock<shared_mutex> lk(shared_mtx), shared_mtx.lock() is exclusive lock!
5. shared_lock: to lock shared_mutex on read so read actions are not blocking each other.
6. unique_lock/lock_guard: to lock write action.

```cpp
// use shared_mutex with shared_lock and unique_lock
int cnt;
shared_mutex mtx; // use shared_lock with shared_mutex can enable concurrent read
int read() {
    shared_lock<shared_mutex> lk(mtx);
    return cnt;
}
void write(int v) {
    unique_lock<shared_mutex> lk(mtx); // use lock_guard is better here as we don't need complex control over the lock here
    cnt = v;
}
```
