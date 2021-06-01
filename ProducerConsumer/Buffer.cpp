//
//  Buffer.cpp
//  ProducerConsumer
//
//  Created by Andrew Wei on 5/31/21.
//

#include <iostream>
#include "Buffer.hpp"

Buffer::Buffer() {
    buffer_size = 0;
    left = 0;
    right = 0;
}

void Buffer::produce(int num) {
    // Acquire a unique lock on the mutex
    std::unique_lock<std::mutex> unique_lock(mtx);
    std::cout << "produce called " << num << "\n";
    
    // Wait if the buffer is full
    not_full.wait(unique_lock, [this]() {
        std::cout << "produce " << buffer_size << "\n";
        return buffer_size != BUFFER_CAPACITY;
    });
    
    // Add input to buffer
    buffer[right] = num;
    
    // Update appropriate fields
    right = (right + 1) % BUFFER_CAPACITY;
    buffer_size++;
    
    std::cout << "produce buffer size " << buffer_size << "\n";
    
    // Unlock unique lock
    unique_lock.unlock();
    
    // Notify a single thread that buffer isn't empty
    not_empty.notify_one();
}

int Buffer::consume() {
    // Acquire a unique lock on the mutex
    std::unique_lock<std::mutex> unique_lock(mtx);
    std::cout << "consume called\n";
    
    // Wait if buffer is empty
    not_empty.wait(unique_lock, [this]() {
        std::cout << "consume " << buffer_size << "\n";
        return buffer_size != 0;
    });
    
    // Getvalue from position to remove in buffer
    int result = buffer[left];
    
    std::cout << "Consumed: " << result << "\n";
    
    // Update appropriate fields
    left = (left + 1) % BUFFER_CAPACITY;
    buffer_size--;
    std::cout << "consume buffer size " << buffer_size << "\n";
    
    // Unlock unique lock
    unique_lock.unlock();
    
    // Notify a single thread that the buffer isn't full
    not_full.notify_one();
    
    // Return result
    return result;
}
