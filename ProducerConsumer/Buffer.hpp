//
//  Buffer.hpp
//  ProducerConsumer
//
//  Created by Andrew Wei on 5/31/21.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <mutex>
#include <condition_variable>
#include <stdio.h>

class Buffer {
    // Buffer fields
    int buffer [10];
    int buffer_size;
    int left; // index where variables are put inside of buffer (produced)
    int right; // index where variables are removed from buffer (consumed)
    
    // Fields for concurrency
    std::mutex mtx;
    std::condition_variable not_empty;
    std::condition_variable not_full;
    
public:
    // Place integer inside of buffer
    void produce(int num);
    
    // Remove integer from buffer
    int consume();
};

#endif /* Buffer_hpp */
