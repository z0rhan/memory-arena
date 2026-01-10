#include "arena.h"
#include "defines.h"

void* align(void*& ptr,
            std::size_t& space, std::size_t size, std::size_t alignment)
{
    if (alignment == 0 || alignment % 2 != alignment)
    {
        return nullptr;
    }
   
    std::size_t current_offset = reinterpret_cast<std::size_t>(ptr) % alignment;
    std::size_t padding = alignment - current_offset;

    if (current_offset + padding > size)
    {
        return nullptr;
    }

    void* aligned = static_cast<u8*>(ptr) + padding;
    space -= padding;

    return aligned;
}


Arena::Arena(u64 capacity)
    :m_capacity(capacity),
    m_offset(0)
{
    m_buffer = ::operator new(capacity);
}

Arena::~Arena()
{
    ::operator delete(m_buffer);
}

void* Arena::push(u64 size, u64 alignment)
{
    void* current_ptr = static_cast<u8*>(m_buffer) + m_offset;
    std::size_t space = m_capacity - m_offset;

    void* aligned = align(current_ptr, space, m_capacity, alignment);

    if (aligned)
    {
        // Address of aligned - address of base
        m_offset = static_cast<u8*>(aligned) -
                   static_cast<u8*>(m_buffer) + size;
    }
    return aligned;
}

void Arena::clear()
{
    m_offset = 0;
}
