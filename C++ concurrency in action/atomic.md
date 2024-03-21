### atomic vs mutex
1. Atomic operations are used to perform simple operations (like increment, decrement, load, store) on a single variable in a way that these operations are indivisible.
2. Generally, atomic operations are faster than mutexes for simple operations on a single variable because they don't involve the overhead of context switches or kernel transitions that mutex locking might incur.They are implemented on hardware level
3. Mutexes (mutual exclusions) are used to protect a block of code or a data structure so that only one thread can access it at a time.  
```cpp
// both read and write of an atomic variable are atomic, however it may still cause race condition if not handle the atomic correct if there's a compund operation
atomic<int> counter(0);
// e.g. there are two thread A and B, A read counter -> B read counter -> A write counter -> B write counter, counter incremented from 0 to 2
increment() {
    if (counter < 1) {
        counter++;
    }
}
```
