#ifndef MEMORY_SIMPLE_H
#define MEMORY_SIMPLE_H

#include "memory.h"
#include "mystring.h"

class memory_simple final : public memory
{
private:

    logger* _log_memory;

public:

    class AllocateError {};

public:

    memory_simple(logger* logger);


    void *allocate(size_t target_size) const override;

    void deallocate(void const* const target_to_dealloc) const override;

};

#endif