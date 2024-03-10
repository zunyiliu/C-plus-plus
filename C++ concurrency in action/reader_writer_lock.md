```cpp
int cnt;
shared_mutex mtx; // use shared_lock with shared_mutex can enable concurrent read
int read() {
    shared_lock<shared_mutex> lk(mtx);
    return cnt;
}
void write(int v) {
    unique_lock<shared_mutex> lk(mtx);
    cnt = v;
}
```
