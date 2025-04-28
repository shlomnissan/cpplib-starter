#include <print>

#include <cpplib/vector2.hpp>

auto main() -> int {
    const auto v = cpplib::Vector2 {3.0f, 4.0f};
    std::print("{}\n", v.Length());

    return 0;
}
