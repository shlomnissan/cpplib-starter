// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "cpplib/vec2.hpp"

#include <cmath>

using namespace mat;

vec2::vec2(float x, float y) : x(x), y(y) {}

auto vec2::magnitude() const -> float {
    return std::sqrt(x * x + y * y);
}