/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file starry_background.h
 * @brief Background Manager.
 *
 * - \subpage Subsystem: Space Invaders
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

#include "random.h"

/**
 * @class StarryBackground
 * @brief Background Renderization.
 */
class StarryBackground {
 public:
  StarryBackground();

  void update(float dt);

  void draw(sf::RenderTarget& renderer);

 private:
  void giveStarRandomStartLocation(sf::Vertex& v);

  std::vector<sf::Vertex> m_stars;

  Random<> m_rng;
};
/** @} */