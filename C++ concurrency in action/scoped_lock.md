```cpp
mutex mtx1;
mutex mtx2;
scoped_lock lk(mtx1, mtx2);
```
#### scoped_lock vs lock_guard vs unique_lock
lock_guard is the basic lock, it's faster but it only provides management of mutex(don't need to unlock explicity yourself);
scoped_lock is just a upgraded lock_guard but can lock multiple mtx at the same time.
unique_lock is a upgraded lock_guard but can lock/unlock mutex felexibily.
