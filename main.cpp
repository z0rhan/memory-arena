// Usage example

#include "arena.h"

#include <iostream>

struct test
{
    int x, y, z;
    inline void do_smthg()
    {
        std::cout << "Doing smthg\n";
    }
};

int main(void)
{
    Arena arena(512);

    test* res = arena.push_type<test>();
    res->do_smthg();

    arena.clear();

    return 0;
}
