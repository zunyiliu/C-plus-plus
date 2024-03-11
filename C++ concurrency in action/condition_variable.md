### condition_variable
1. std::condition_variable is specifically designed to work with std::mutex through std::unique_lock<std::mutex>. It cannot directly work with other types of mutexes, such as std::shared_mutex.
2. notify_one: only one thread will be waken, if multiple threads are waiting then one of them(not specified) will be waken.
3. notify_all: all waiting threads will be waken.









#### Lambda that used in condition_variable
https://github.com/zunyiliu/C-plus-plus/blob/main/C%2B%2B%20concurrency%20in%20action/avoid%20deadlock.md
