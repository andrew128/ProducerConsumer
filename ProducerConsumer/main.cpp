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
    // Generate random number between 1 and 10
    int new_int = rand() % 10 + 1;
    
    std::cout << "Produced: " << new_int << "\n";
    
    buffer.produce(new_int);
}

// Takes in reference to a buffer and returns the latest int added
// in the buffer
void consumeInt(Buffer &buffer) {
    int result = buffer.consume();
    
    std::cout << "Consumed: " << result << "\n";
}

int main(int argc, const char * argv[]) {
    std::cout << "Executing code in main...\n";
    
    // Initialize random seed
    srand (time(NULL));
    
    // Create Buffer
    Buffer buffer;
    
    // Create a thread to produce
    std::thread produceThread(produceInt, std::ref(buffer));
    
    // Create a thread to consume
    std::thread consumeThread(consumeInt, std::ref(buffer));
    
    produceThread.join();
    consumeThread.join();
    
    std::cout << "Done!\n";
    return 0;
}
