// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <gtest/gtest.h>

#include "utils/sqrt.hpp"

TEST(sqrt, perfect_square) {
    auto f = sqrt(25.f);

    EXPECT_EQ(f, 5.f);
}