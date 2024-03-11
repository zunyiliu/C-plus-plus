### condition_variable
1. std::condition_variable is specifically designed to work with std::mutex through std::unique_lock<std::mutex>. It cannot directly work with other types of mutexes, such as std::shared_mutex.










#### Lambda that used in condition_variable
https://github.com/zunyiliu/C-plus-plus/blob/main/C%2B%2B%20concurrency%20in%20action/avoid%20deadlock.md
