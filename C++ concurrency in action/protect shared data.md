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
```
