#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

/**
 * queue_t is a thread safe queue used in the algorithms I will be writing
*/

template <typename T>
class queue_t {
private:
    std::queue<T> data;
    std::mutex mtx;
    std::condition_variable cv;

public:
    queue_t();
    queue_t(const queue_t& que_t);
    /**
     * Deleted for now to make implementation easier
    */
    queue_t &operator=(const queue_t&) = delete;
    /**
     * Safely adding a new_value to the queue
    */
    void push(T &val);
    /**
     * Tries to get a value from the queue, if it finds nothing
     * it quits immediatly and returns false else it affects the value
     * to new_val and then removes it
    */
    bool try_pop(T &val);

    /**
     * Returns a shared pointer, because we make the pointer and pop the value
    */
    std::shared_ptr<T> try_pop();

    /**
     * Waits until a value is found and then affects it to val
     * and then pops the element
    */
    void wait_pop(T& val);

    /**
     * Waits until a value is found and then make a shared_ptr
     * and then pops the element. Finally we return the pointer
    */
   std::shared_ptr<T> wait_pop();

   bool empty() const;
};

template<typename T>
queue_t<T>::queue_t(const queue_t<T>& que_t) {
    std::lock_guard<std::mutex> lck(que_t.mtx);
    data = que_t.data;
    lck.unlock();
    cv.notify_one();
}

template<typename T>
void queue_t<T>::push(T& val) {
    data.push(val);
}

template<typename T>
bool queue_t<T>::try_pop(T &val) {
    std::lock_guard<std::mutex> lck(mtx);
    if (!data.empty()) {
        return false;
    }
    val = data.front();
    data.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> queue_t<T>::try_pop() {
    std::lock_guard<std::mutex> lck(mtx);
    if (data.empty()) {
        return std::shared_ptr<T>();
    }
    std::shared_ptr<T> result(std::make_shared<T>(data.front()));
    data.pop();
    return result;
}

template<typename T>
void wait_pop(T& val) {
    std::unique_lock<T> lck(mtx);
    cv.wait(lck, [this]{ return !data.empty();});
    val = data.front();
    return val;
}

template<typename T>
std::shared_ptr<T> queue_t<T>::wait_pop() {
    std::unique_lock<T> lck(mtx);
    cv.wait(lck, [this]{ return !data.empty();});
    std::shared_ptr<T> result(std::make_shared<T>(data.front()));
    data.pop();
    return result;
}

template<typename T>
bool queue_t<T>::empty() const {
    std::lock_guard<T> lck(mtx);
    return data.empty();
}