//
//  Buffer.cpp
//  ProducerConsumer
//
//  Created by Andrew Wei on 5/31/21.
//

#include "Buffer.hpp"

void Buffer::produce(int num) {
    // Acquire a unique lock on the mutex
    std::unique_lock<std::mutex> unique_lock(mtx);
    
    // Wait if the buffer is full
    not_full.wait(unique_lock, [buffer_size_copy = buffer_size]() {
        return buffer_size_copy != BUFFER_CAPACITY;
    });
    
    // Add input to buffer
    buffer[left] = num;
    
    // Update appropriate fields
    left = (left + 1) % BUFFER_CAPACITY;
    buffer_size++;
    
    // Unlock unique lock
    unique_lock.unlock();
    
    // Notify a single thread that buffer isn't empty
    not_empty.notify_one();
}

int Buffer::consume() {
    // Acquire a unique lock on the mutex
    std::unique_lock<std::mutex> unique_lock(mtx);
    
    // Wait if buffer is empty
    not_empty.wait(unique_lock, [buffer_size_copy = buffer_size]() {
        return buffer_size_copy != 0;
    });
    
    // Getvalue from position to remove in buffer
    int result = buffer[right];
    
    // Update appropriate fields
    right = (right - 1) % BUFFER_CAPACITY;
    buffer_size--;
    
    // Unlock unique lock
    unique_lock.unlock();
    
    // Notify a single thread that the buffer isn't full
    not_full.notify_one();
    
    // Return result
    return result;
}
