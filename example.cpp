#include "union_of.hpp"

#include <cstdint>
#include <iostream>

struct __attribute__((packed)) rgba
{
    uint8_t r, g, b, a;
};

struct __attribute__((packed)) two_u16
{
    uint16_t low;
    uint16_t high;
};

int main()
{
    const char *some_binary_data = "\x00\x40\x9a\x44";

    union_of<int, float, rgba, two_u16> u{some_binary_data, union_set_data_tag{}};

    static_assert(sizeof(u) == 4);

    std::cout << "As int:\t\t" << int(u) << '\n';
    std::cout << "As float:\t" << float(u) << '\n';

    const auto &c = rgba(u);
    std::cout << "As rgba:\t" << int(c.r) << ' ' << int(c.g) << ' ' << int(c.b) << ' ' << int(c.a) << '\n';

    std::cout << "\nLow: " << std::hex << two_u16(u).low << ", high: " << two_u16(u).high << '\n';

    return 0;
}
