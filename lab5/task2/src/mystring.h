#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <string>
#include <sstream>

std::string address_to_str(const void*);
std::string bytes_from_mem(const void*, size_t);

#endif