/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file collidable.h
 * @brief Collision tracker.
 *
 * - \subpage Subsystem: Space Invaders
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

/**
 * @class Collidable
 * @brief Colision handler class.
 */
class Collidable {
 public:
  Collidable(float width, float height);

  bool tryCollideWith(Collidable& other);
  sf::FloatRect getBox() const;

  virtual const sf::Vector2f& getPosition() const = 0;
  virtual void onCollide(Collidable& other) = 0;

 private:
  sf::Vector2f m_size;
};
/** @} */