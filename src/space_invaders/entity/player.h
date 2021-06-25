/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file player.h
 * @brief Player representation.
 *
 * - \subpage Subsystem: Space Invaders Entity
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_entity */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>

#include "collidable.h"

#include "animation.h"

/**
 * @class Player
 * @brief Represents the player.
 */
class Player : public Collidable {
 public:
  constexpr static int kWidth = 44;
  constexpr static int kHeight = 32;

  Player();

  void input();
  void update(float dt);
  void draw(sf::RenderTarget& target);

  // Gets the coordinates of the gun
  sf::Vector2f getGunPosition() const;

  const sf::Vector2f& getPosition() const;
  void onCollide(Collidable& other) override;

  int getLives() const;
  bool isAlive() const;

  void tryRevive();

 private:
  void restart();

  sf::RectangleShape m_sprite;
  Animation m_death_animation;
  sf::Vector2f m_velocity;
  sf::Clock m_death_timer;

  bool m_is_alive = true;
  int m_lives_left = 3;

  sf::Sound m_death_sound;
};
/** @} */