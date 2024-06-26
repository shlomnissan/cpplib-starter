// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "cpplib/vec2.hpp"

TEST(vec2, magnitude) {
    auto v = cpplib::vec2 {3.f, 4.f};

    EXPECT_EQ(v.magnitude(), 5.f);
}