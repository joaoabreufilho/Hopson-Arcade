/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file random.h
 * @brief Random numbers getter.
 *
 * - \subpage Subsystem: Arcade Resources
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_resources */
/** @{ */
#pragma once

#include <ctime>
#include <random>
/**
 * @class Random
 * @brief Template class to get random numbers.
 */
template <typename Engine = std::mt19937>
class Random {
  template <typename T>
  using UniformDist = std::uniform_real_distribution<T>;
  using UniformIntDist = std::uniform_int_distribution<int>;

 public:
  static Random m_g_rand;

  Random(int seed = std::time(nullptr)) : m_prng(seed) {}

  int getIntInRange(int low, int high) {
    return getNumberInRange<UniformIntDist>(low, high);
  }

  float getFloatInRange(float low, float high) {
    return getNumberInRange<UniformDist<float>>(low, high);
  }

  template <typename T>
  T getNumberInRange(T low, T high) {
    return getNumberInRange<UniformDist<T>>(low, high);
  }

  template <typename Dist, typename T>
  T getNumberInRange(T low, T high) {
    Dist dist(low, high);
    return dist(m_prng);
  }

 private:
  Engine m_prng;
};
/** @} */