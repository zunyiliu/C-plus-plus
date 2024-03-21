1. mutex, the most common way by adding lock.
2. some data is read-only, then we only need to add lock during initialisating, and after that the data will not be modified at all thus lock is not needed.
```cpp
// a bad example for double-checked locking
void undefined_behaviour_with_double_checked_locking() {
    if (!resource_ptr) {
        lock_guard<mutex> lg(resource_mutex);
        if (!resource_ptr) {  // in c++, if a thread modifies a resource, it's not guaranteed other resources will see the update immediately, it may have a 'lag'
            resource_ptr.reset(new some_resource);
        }
    }
    resource_ptr -> do_something();
}
// solution -- the resource_ptr needs to be changed to atomic, it's possible that threadA is init the resource_ptr and threadB finds if(!resource_ptr) returns true thus letting
// recourse_ptr to do_something() before the resource is fully reset by threadA

// good example using call_once and once_flag
class X {
private:
    connection_info detail;
    connection_handle connection;
    once_flag flag;
    void open_connection() {
        connection = connection_manager.open(detail);
    }
public:
    X(connection_info const& detail_): detail(detail_) {}
    void send_data(data_package const& data) {
        call_once(flag, &X::open_connection(), this);
        connection.send_data(data)
    }
    data_package receive_data() {
        call_once(flag, &X::open_connection(), this);
        return connection.receive_data();
    }
}
// another way to keep thread safe in C++ 11 or above
// singleton
class my_class {
public:
    my_class() {
        cout << "constructed" << endl; // this will only be called once no matter how many threads called get_my_class()
    }
};
my_class& get_my_class() {
    static my_class instance;
    return instance;
}
```

### FAQ
mutex and once_flag can't be copied or moved
