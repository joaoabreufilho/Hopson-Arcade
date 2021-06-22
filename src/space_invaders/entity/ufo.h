/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file ufo.h
 * @brief UFO entity handler.
 *
 * - \subpage Subsystem: Space Invaders Entity
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_entity */
/** @{ */
#pragma once

#include "animation.h"
#include "random.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "collidable.h"

/**
 * @class UFO
 * @brief UFO entity handler.
 */
class UFO : public Collidable {
 public:
  enum class State { kWaiting, kFlying, kDestroyed };

  UFO(Random<>& rand);

  State getState() const;

  void update(float dt);

  void draw(sf::RenderTarget& window);

  const sf::Vector2f& getPosition() const;
  void onCollide(Collidable& other);

 private:
  Random<>& m_rng;

  sf::RectangleShape m_sprite;
  float m_vx;
  State m_state;
  Animation m_animation;

  sf::Sound m_flying_sound;
};
/** @} */