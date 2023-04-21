#include "memory_simple.h"

memory_simple::memory_simple(logger* logger) : _log_memory(logger) {}

void *memory_simple::allocate(size_t target_size) const
{
    try
    {
        void *res_mem = ::operator new(sizeof(size_t) + target_size);
        auto block_size = reinterpret_cast<size_t*>(res_mem);
        *block_size = target_size;
        std::string str_address = address_to_str(res_mem);

        _log_memory->log("allocate at address:" + str_address, logger::severity::trace);
        return reinterpret_cast<void*>(block_size + 1);
    }
    catch(std::bad_alloc)
    {
        throw AllocateError();
    }
}

void memory_simple::deallocate(void const* const target_to_dealloc) const
{
    auto target_block = reinterpret_cast<void*>(reinterpret_cast<size_t*>(const_cast<void*>(target_to_dealloc)) - 1);
    auto block_size = reinterpret_cast<size_t*>(target_block);
    std::cout << *block_size << "\n";
    std::string str_address = address_to_str(target_block);
    std::string bytes = bytes_from_mem(target_to_dealloc, *block_size);

    _log_memory->log("deallocate at address:" + str_address + " " + bytes, logger::severity::trace);
    ::operator delete(const_cast<void*>(target_block));
}