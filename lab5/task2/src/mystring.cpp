#include "mystring.h"

std::string address_to_str(const void* ptr)
{
    std::string res;
    std::ostringstream oss;
    oss << ptr;
    res = oss.str();
    return res;
}

std::string bytes_from_mem(const void* ptr, size_t block_size)
{
    std::string res = "[";
    auto iter = reinterpret_cast<unsigned char*>(const_cast<void*>(ptr));
    for(int i = 0; i < block_size; i++){
        res += std::to_string(static_cast<unsigned short>(*iter++));
        if(block_size - i > 1)
            res += " ";
    }
    res += "]";
    return res;
}