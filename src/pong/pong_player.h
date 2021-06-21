/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file pong player.h
 * @brief Pong player definition.
 *
 * - \subpage Subsystem: Pong
 *
 * \date Jun 2021
 */
/** @addtogroup pong */
/** @{ */
#pragma once

#include "net.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <string>

/**
 * @brief Player direction.
 */
enum class PongPlayerDirection {
  UpDown,
  LeftRight,
};

/**
 * @brief A client-side player. This is either the player, a peer, or a "AI"
 * player
 */
struct PongPlayer {
  std::string name;
  int score = 0;
  bool isConnected = false;

  sf::RectangleShape paddle;
  PongPlayerDirection direction;
};

using PongClientPlayerList = std::array<PongPlayer, kMaxConnects>;
/** @} */