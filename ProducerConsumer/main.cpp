//
//  main.cpp
//  ProducerConsumer
//
//  Created by Andrew Wei on 5/30/21.
//

#include <thread>
#include <iostream>
#include "Buffer.hpp"
#include <stdlib.h>

// Takes in reference to a buffer and adds a random integer
void produceInt(Buffer &buffer) {
    for (int i = 0; i < 4; i++) {
        // Generate random number between 1 and 10
        int new_int = rand() % 10 + 1;
        buffer.produce(i, new_int);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Takes in reference to a buffer and returns the latest int added
// in the buffer
void consumeInt(Buffer &buffer) {
    for (int i = 0; i < 6; i++) {
        buffer.consume(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Executing code in main...\n";
    
    // Initialize random seed
    srand (time(NULL));
    
    // Create Buffer
    Buffer buffer;
    
    // Create a thread to produce
    std::thread produceThread0(produceInt, std::ref(buffer));
    
    std::thread consumeThread0(consumeInt, std::ref(buffer));
    
    std::thread produceThread1(produceInt, std::ref(buffer));
    
    std::thread consumeThread1(consumeInt, std::ref(buffer));
    
    std::thread produceThread2(produceInt, std::ref(buffer));
    
    produceThread0.join();
    produceThread1.join();
    produceThread2.join();
    consumeThread0.join();
    consumeThread1.join();
    
    std::cout << "Done!\n";
    return 0;
}
