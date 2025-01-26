#pragma once

#include <condition_variable>
#include <mutex>
#include <semaphore>
#include <array>

template<typename T>

class Queue {

public:

    bool has_done() {
        std::unique_lock<std::mutex> lock(mtx_);
        return has_done_;
    }

    void set_has_done() {
        std::unique_lock<std::mutex> lock(mtx_);
        has_done_ = true;
    }

    void push(const T& item) {
        empty_slots.acquire();
        std::unique_lock<std::mutex> lock(mtx_);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        filled_slots.release();
    }

    void pop(T& item) {
        filled_slots.acquire();
        std::unique_lock<std::mutex> lock(mtx_);
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        empty_slots.release();
    }

private:

    static constexpr int BUFFER_SIZE = 20;
    std::array<std::pair<std::vector<double>, int>, BUFFER_SIZE> buffer;
    std::mutex mtx_;
    int in = 0;
    int out = 0;
    std::counting_semaphore<BUFFER_SIZE> empty_slots(BUFFER_SIZE) {};
    std::counting_semaphore<0> filled_slots(0) {};      
    bool has_done_ = false;

};