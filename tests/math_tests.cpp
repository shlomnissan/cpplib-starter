// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#include <gtest/gtest.h>

#include "math.hpp"

TEST(Math, Sqrt) {
    EXPECT_FLOAT_EQ(cpplib::sqrt(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(cpplib::sqrt(1.0f), 1.0f);
    EXPECT_FLOAT_EQ(cpplib::sqrt(4.0f), 2.0f);
    EXPECT_FLOAT_EQ(cpplib::sqrt(9.0f), 3.0f);
    EXPECT_FLOAT_EQ(cpplib::sqrt(16.0f), 4.0f);
    EXPECT_FLOAT_EQ(cpplib::sqrt(25.0f), 5.0f);
}