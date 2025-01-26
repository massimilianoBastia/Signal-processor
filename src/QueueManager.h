#pragma once

#include <mutex>
#include "Queue.h"
#include <vector>

class QueueManager
{

    Queue<std::pair<std::vector<double>, int>> buffer;

    std::pair<std::vector<double>, int> pop() {

    }

    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.push(item);
        cv_.notify_one();
    }


    Queue<std::pair<std::vector<double>,int>> acquire() const {
        std::unique_lock<std::mutex> lock(mtx_);
        return queue_buffers
    }

    bool has_done() const {
        std::unique_lock<std::mutex> lock(mtx_);
        return done_;
    }

    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.push(item);
        cv_.notify_one();
    }

    bool try_pop(T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (queue_.empty()) return false;
        item = queue_.front();
        queue_.pop();
        cv_.notify_one();
        return true;
    }

    private: 

        Queue<std::pair<std::vector<double>, int>> queue_1;
        Queue<std::pair<std::vector<double>, int>> queue_2;
        mutable std::mutex mtx_;
        std::condition_variable cv_;




};

