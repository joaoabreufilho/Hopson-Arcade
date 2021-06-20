/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file non_copyable.h
 * @brief Define an non-movable entity.
 *
 * - \subpage Subsystem: Arcade Resources
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_resources */
/** @{ */
#pragma once

/// @brief Define an non-movable struct.
struct NonMovable {
  NonMovable() = default;
  NonMovable& operator=(NonMovable&&) = delete;
  NonMovable(NonMovable&&) = delete;
};
/** @} */