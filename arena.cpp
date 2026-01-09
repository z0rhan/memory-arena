#include "arena.h"
#include "defines.h"

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

void Arena::pop(u64 size)
{
    size = MIN(size, reinterpret_cast<u8*>(m_offset) -
                     reinterpret_cast<u8*>(m_buffer));
    m_offset -= size;
}

void Arena::clear()
{
    m_offset = 0;
}
