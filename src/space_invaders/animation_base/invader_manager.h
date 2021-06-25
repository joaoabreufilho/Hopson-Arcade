/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file invader_manager.h
 * @brief Drawing and updating invader manager.
 *
 * - \subpage Subsystem: Space Invaders
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders */
/** @{ */
#pragma once

#include "animation_renderer.h"
#include "display_info.h"
#include "invader.h"
#include "projectile.h"

#include <SFML/Audio.hpp>
#include <vector>

#include <random.h>

class World;

using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

/**
 * @class InvaderManager
 * @brief Class to manage the drawing and updating of invaders.
 */
class InvaderManager {
 public:
  InvaderManager(World& world);

  /**
   * Moves all of the invaders to the left or right, if the clock has reached a
   * certain time.
   *
   * @param void
   *
   * @return void
   */

  void tryStepInvaders();

  /**
   * Draws all of the alive invaders
   *
   * @param target Tanget render entity.
   *
   * @return void
   * @note Uses target reference.
   */
  void drawInvaders(sf::RenderTarget& target);

  /**
   *   Tries to collide the invaders with the projectiles,
   *
   * @param target Tanget render entity.
   *
   * @return CollisionResult Points of collision.
   */
  CollisionResult tryCollideWithProjectiles(
      std::vector<Projectile>& projectiles);

  /**
   * This is for firing projectiles from the enemy
   *
   * @param random Reference of Random object.
   *
   * @return Vector point.
   */
  sf::Vector2f getRandomLowestInvaderPoint(Random<>& random);

  int getAliveInvadersCount() const;

  /**
   * These two functions are for the initilization of the invaders. It will add
   * one invader at a time unil all have been added.
   *
   * @param void
   *
   * @return void
   */
  void initAddInvader();
  bool areInvadersAlive() const;

 private:
  /**
   * Changes time between the alien's steps based on number alive.
   *
   * @param void
   *
   * @return void
   */
  void updateStepDelay();

  /**
   * Checks the invaders position to see if all the aliens should move down Or
   * if the game is over
   *
   * @param invader Invader reference.
   *
   * @return true if all the aliens should move down.
   */
  bool testInvaderPosition(const Invader& invader) const;

  std::vector<Invader> m_invaders;
  sf::Clock m_step_timer;
  sf::Time m_step_gap;

  World& m_world;

  AnimationRenderer m_invader_renderer;
  unsigned m_alive_invaders = 0;

  bool m_has_all_invaders_been_added = false;

  bool m_is_moving_left = false;
  bool m_move_down = false;

  int m_init_x = 0;
  int m_init_y = 4;
  int m_ticks = 0;

  sf::Sound m_step_sounds[4];
  sf::Sound m_invader_killed_sound;
};
/** @} */