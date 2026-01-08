#ifndef ARENA_HH
#define ARENA_HH

#include "defines.h"

class Arena
{
public:
    Arena(u64 capacity);
    ~Arena();

    template<typename T>
    T* push_type()
    {
        return static_cast<T*>(push(sizeof(T), alignof(T)));
    }

    void clear();

private:
    void* push(u64 size, u64 alignment);

private:
    std::size_t m_capacity;
    std::size_t m_offset;
    void* m_buffer;
};


#endif // ARENA_HH
