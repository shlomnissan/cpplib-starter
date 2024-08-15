// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "cpplib_export.h"

namespace cpplib {
    /**
     * @brief Represents a 2D vector with x and y components.
     */
    class CPPLIB_EXPORT vec2 {
    public:
        /**
         * @brief The x component of the vector.
         */
        float x {0};

        /**
         * @brief The y component of the vector.
         */
        float y {0};

        /**
         * @brief Constructs a new `vec2` object with specified x and y components.
         *
         * @param x The x-coordinate of the vector.
         * @param y The y-coordinate of the vector.
         */
        vec2(float x, float y);

        /**
         * @brief Computes the magnitude (length) of the vector.
         *
         * @return float The magnitude of the vector.
         */

        [[nodiscard]] auto magnitude() const -> float;
    };
}