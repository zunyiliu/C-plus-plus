1. sometimes can do things like this lock(mtx1, mtx2, mtx3..)
2. AVOID NESTED LOCKS -- don’t acquire a lock if you already hold one. If each thread only ever holds a single lock then you will never have deadlock.
3. AVOID CALLING USER-SUPPLIED CODE WHILE HOLDING A LOCK -- you have no control of user's code, it's possible the user code has a lock and you holding a lock as well which causes nested lock.
4. ACQUIRE LOCKS IN A FIXED ORDER -- acquire locks in same order in every thread.
```cpp
do_something1() {
  lock_guard<mutex> lg1(mtx1);
  lock_guard<mutex> lg2(mtx2);
  lock_guard<mutex> lg3(mtx3);
}

do_something2() {
  lock_guard<mutex> lg1(mtx1);
  lock_guard<mutex> lg2(mtx2);
  lock_guard<mutex> lg3(mtx3);
}

int main() {
  thread t1(do_something1);
  thread t2(do_something2);
  return 0;
}
```
5. USE A LOCK HIERARCHY -- each mutex is assigned a hierarchy level (usually a numeric value), and a thread can only lock a mutex if it's not already holding a mutex of a lower or equal hierarchy level.
   each mutex has a hierarchy level, when a thread wants to lock a mutex, it first checks if the current level is great than the mutex's level, if so lock the mutex and set thread's level to mutex's level.
   (It's just sort mutex in desc order, and let threads lock mutex based on a desc order).
