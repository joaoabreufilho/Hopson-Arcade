/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file explosion.h
 * @brief Explosion entity handler.
 *
 * - \subpage Subsystem: Space Invaders Entity
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_entity */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

/**
 * @class StateLobby
 * @brief Represents a single explosion entity.
 */
class Explosion {
 public:
  Explosion(const sf::Vector2f& position);

  bool isLifeOver() const;
  const sf::Vector2f& getPosition() const;

 private:
  sf::Vector2f m_position;      // The position of the explosion
  sf::Clock m_lifetime_counter;  // Clock for checking if the explosion is
                                // outlived
};
/** @} */