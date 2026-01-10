// Very minimal memory arena implementation

#ifndef ARENA_HH
#define ARENA_HH

#include "defines.h"

// something like std::align
void* align(void*& ptr,
            std::size_t& space, std::size_t size, std::size_t alignment);

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

    // Pop was incorrect since we also need to take care of padding and alignment
    // Not worth it for me for now

    void clear();

private:
    void* push(u64 size, u64 alignment);

private:
    u64 m_capacity;
    u64 m_offset;
    void* m_buffer;
};


#endif // ARENA_HH
