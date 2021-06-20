/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file maths.h
 * @brief Util math definitions.
 *
 * - \subpage Subsystem: Arcade Resources
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_resources */
/** @{ */
#pragma once

constexpr float kPi = 3.14159265f;
constexpr float kMinPi = 3.14f;

template <typename T>
T toRadians(T degrees) {
  return degrees * kPi / 180;
}

template <typename T>
T toDegrees(T radians) {
  return (radians * 180) / kPi;
}
/** @} */