### std::future
future is used to access the result of an asynchronous operation. The main difference from thread is future can get return value, also future can capture and handle exception whereas thread can only handle exception within the thread itself.
#### future typees
1. std::launch::async, guarantees that the task will be executed on a new thread asynchronously.
2. std::launch::deferred, the task is not started immediately. Instead, it is executed lazily, only when its result is explicitly requested (e.g., via future.get() or future.wait()). 
3. std::launch::async | std::launch::deferred, the implementation may choose to execute the callable object either immediately on a new thread or defer its execution until the std::future's get() or wait() is called.
4. without first param, is equivalent to std::launch::async | std::launch::deferred.
#### future with async
```cpp
int calculate(int x, int y) {
    // simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x + y;
}
int main() {
    future<int> future = std::async(std::launch::async, calculate, 3, 4);
    cout << future.get() << endl; // future.wait() is just waiting without getting the returned value
    return 0;
}

class Obj {
public:
    int sum(int x, int y) {
        this_thread::sleep_for(chrono::milliseconds(1000));
        return x + y;
    }
};
int main() {
    Obj obj;
    future<int> f = async(&Obj::sum, &obj, 3, 4);
    std::cout << f.get() << endl;
    return 0;
}
```
#### future with promise
```cpp
void producer(promise<int>& p) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    p.set_value(33);
}
void consumer(future<int>& f) {
    int val = f.get();
    cout << val << endl;
}
int main() {
    promise<int> promise;
    future<int> future = promise.get_future();
    thread t1(producer, ref(promise));
    thread t2(consumer, ref(future));
    t1.join();
    t2.join();
    return 0;
}
```
#### future with packaged_task
```cpp
// packaged_task encapsulates a task that can be executed asynchronously
int main() {
    packaged_task<int(int, int)> task([](int const& a, int const& b){
        this_thread::sleep_for(chrono::milliseconds(1000));
        return a + b;        
    });
    future<int> f = task.get_future();
    thread t(move(task), 3, 5);
    cout << f.get() << endl;
    t.join();
    return 0;
}
```
### std::shared_future
allows multiple accesses to the result of an asynchronous operation.
