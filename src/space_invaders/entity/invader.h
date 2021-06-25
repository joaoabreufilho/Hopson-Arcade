/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file invader.h
 * @brief Invader entity handler.
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
 * @class Invader
 * @brief Class to represent a single invader
 */
class Invader : public Collidable {
 public:
  enum class Type {
    kOctopus,
    kCrab,
    kSquid,
  };

  Invader(const sf::Vector2f& initialLocation, Type type);

  void move(float x, float y);

  const sf::Vector2f& getPosition() const;
  bool isAlive() const;
  Type getType() const;

  void onCollide(Collidable& other) override;

  void makeAlive() {
    m_is_alive = true;
    m_location = m_initial_position;
  }

 private:
  const sf::Vector2f m_initial_position;
  sf::Vector2f m_location;
  bool m_is_alive = false;
  Type m_type;

 public:
  constexpr static float kWidth = 48;
  constexpr static float kHeight = 32;
};
/** @} */