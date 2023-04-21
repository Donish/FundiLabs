#include <iostream>
#include <string>
#include <vector>
#include "memory_simple.h"
#include "../logger/logger_builder_concrete.h"
#include "../logger/logger_concrete.h"

int main()
{
    logger_builder* _logger_builder = new logger_builder_concrete(); 
    logger *_logger = _logger_builder
    ->add_stream("file.txt", logger::severity::trace)
    ->construct();

    memory *allocator = new memory_simple(_logger);
    
    // char* word = reinterpret_cast<char*>(allocator->allocate(sizeof(char) * 3));
    std::string* strs;
    strs = reinterpret_cast<std::string*>(allocator->allocate(sizeof(std::string) * 3));
    strs[0] = "hello";
    strs[1] = "world!";
    strs[2] = "hi";

    for(int i = 0; i < 3; i++){
        std::cout << strs[i] << "\n";
    }

    allocator->deallocate(strs);
    delete allocator;
    return 0;
}