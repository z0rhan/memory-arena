#ifndef ARENA_HH
#define ARENA_HH

#include "defines.h"

class Arena
{
public:
    Arena(u64 capacity);
    ~Arena();

    template<typename T>
    inline T* push_type()
    {
        void* mem = push(sizeof(T), alignof(T));
        if (!mem)
            return nullptr;

        return new (mem) T();
    }

    template<typename T, typename... Args>
    inline T* push_type(Args&&... args)
    {
        void* mem = push(sizeof(T), alignof(T));
        if (!mem)
            return nullptr;

        return new (mem) T(std::forward<Args>(args)...);
    }

    template<typename T>
    inline void pop_type()
    {
        pop(sizeof(T));
    }

    void clear();

private:
    void* push(u64 size, u64 alignment);
    void pop(u64 size);

private:
    u64 m_capacity;
    u64 m_offset;
    void* m_buffer;
};


#endif // ARENA_HH
