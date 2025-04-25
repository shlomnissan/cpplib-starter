// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <cassert>
#include <cmath>
#include <limits>

namespace cpplib {

auto sqrt(float x) -> float {
    assert(x >= 0.0f);

    if (x == 0.0f || x == 1.0f) return x;

    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    auto guess = x * 0.5f;
    while (true) {
        float next_guess = 0.5f * (guess + x / guess);
        if (std::abs(next_guess - guess) < epsilon) {
            break;
        }
        guess = next_guess;
    }

    return guess;
}

} // namespace cpplib