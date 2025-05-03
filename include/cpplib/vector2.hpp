// Copyright © 2024 - Present, Shlomi Nissan.
// All rights reserved.

#pragma once

#include "cpplib_export.h"

namespace cpplib {

/**
 * @struct Vector2
 * @brief Represents a 2D vector with X and Y coordinates as float values.
 */
struct CPPLIB_EXPORT Vector2 {
    /// @brief X coordinate of the vector.
    float x;

    /// @brief Y coordinate of the vector.
    float y;

    /**
     * @brief Default constructor for Vector2.
     */
    Vector2() : x(0.0f), y(0.0f) {}

    /**
     * @brief Constructor for Vector2 with separate x and y values.
     *
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    Vector2(float x, float y) : x(x), y(y) {}

    /**
     * @brief Calculates the magnitude of the vector.
     *
     * @return float Magnitude of the vector.
     */
    [[nodiscard]] auto Length() const -> float;
};

} // namespace cpplib