/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file world.h
 * @brief Manages interactions between different entites.
 *
 * - \subpage Subsystem: Space Invaders
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

#include "animation_renderer.h"
#include "explosion.h"
#include "invader_manager.h"
#include "player.h"
#include "projectile.h"
#include "shield.h"
#include "ufo.h"

/**
 * @class StarryBackground
 * @brief The class which manages the world and the interactions between
 * different entites
 */
class World {
 public:
  World();

  void input();
  int update(float dt);
  void draw(sf::RenderTarget& target);

  const Player& getPlayer() const;

  bool isGameOver() const;

  void setGameIsOver() { m_is_game_over = true; }

 private:
  void playerProjectileInput();
  void enemyProjectileFire();
  CollisionResult getCollisionResult(float dtt);
  void updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints);

  AnimationRenderer m_projectile_renderer;
  InvaderManager m_invaders;
  Player m_player;
  UFO m_ufo;

  std::vector<Projectile> m_projectiles;
  std::vector<Explosion> m_explosions;
  std::vector<Shield> m_shields;

  sf::RectangleShape m_explode_shape;
  sf::Clock m_invader_shot_clock;
  sf::Clock m_player_shot_clock;
  sf::Clock m_anim_timer;

  sf::Sound m_player_shoot;

  Random<> m_rng;

  bool m_is_game_over = false;
};
/** @} */