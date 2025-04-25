// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include "cpplib/vector2.hpp"

#include "math.hpp"

namespace cpplib {

auto Vector2::Length() const -> float {
    return cpplib::sqrt(x * x + y * y);
}

} // namespace cpplib