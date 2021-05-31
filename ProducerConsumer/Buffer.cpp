//
//  Buffer.cpp
//  ProducerConsumer
//
//  Created by Andrew Wei on 5/31/21.
//

#include "Buffer.hpp"

void Buffer::produce(int num) {
    // Acquire a unique lock on the mutex.
    std::unique_lock<std::mutex> unique_lock(mtx);
    
    // Wait if the buffer is full
    not_full.wait(unique_lock, [buffer_size_copy = buffer_size]() {
        return buffer_size_copy != BUFFER_CAPACITY;
    });
    
    // Add input to buffer
    buffer[left] = num;
    
    // Update appropriate fields
    left = (left + 1) % left;
    buffer_size++;
    
    // Unlock unique lock
    unique_lock.unlock();
    
    // Notify a single thread that buffer isn't empty
    not_empty.notify_one();
}

int Buffer::consume() {
    std::unique_lock<std::mutex> unique_lock(mtx);
    return 0;
}
