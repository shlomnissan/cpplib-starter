// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "cpplib_export.h"

namespace cpplib {
    class CPPLIB_EXPORT vec2 {
    public:
        float x {0};
        float y {0};

        vec2(float x, float y);

        [[nodiscard]] auto magnitude() const -> float;
    };
}