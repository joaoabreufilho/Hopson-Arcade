/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file projectile.h
 * @brief Projectile entity handler.
 *
 * - \subpage Subsystem: Space Invaders Entity
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_entity */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

#include "collidable.h"

/**
 * @class Projectile
 * @brief Projectile handler.
 */
class Projectile : public Collidable {
 public:
  constexpr static float kHeight = 24;
  constexpr static float kWidth = 12;

  enum class Type { kRectangle, kLightning, kKnife };

  enum class Direction { kUp = -1, kDown = 1 };

  Projectile(const sf::Vector2f& position, Type type, Direction direction);
  void update(float dt);
  void onCollide(Collidable& other) override;
  void destroy();

  const sf::Vector2f& getPosition() const;
  Type getType() const;
  bool isActive() const;
  Direction getDirection() const;

  int getID() const;

 private:
  sf::Vector2f m_position;
  Type m_type;
  Direction m_direction;
  bool m_is_active = true;
  int m_id;
};
/** @} */