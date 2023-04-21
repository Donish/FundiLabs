#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include "../logger/logger_concrete.h"

class memory
{
public:

    virtual void *allocate(size_t target_size) const = 0;

public:

    virtual void deallocate(void const* const target_to_dealloc) const = 0;

public:

    virtual ~memory();
};

#endif