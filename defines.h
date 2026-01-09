#ifndef DEFINES_HH
#define DEFINES_HH

#include <cstdint>

using i8    = int8_t;
using u8    = uint8_t;
using i16   = int16_t;
using u16   = uint16_t;
using i32   = int32_t;
using u32   = uint32_t;
using i64   = int64_t;
using u64   = uint64_t;

using b8    = int8_t;
using b32   = int32_t;

#define MIN(a, b) (a < b ? a : b)

inline void*
align(void*& ptr, std::size_t& space, std::size_t size, std::size_t alignment)
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

#endif //DEFINES_HH
