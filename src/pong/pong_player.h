#pragma once

#include "net.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <string>

// A client-side player. This is either the player, a peer, or a "AI" player

enum class PongPlayerDirection {
  UpDown,
  LeftRight,
};

struct PongPlayer {
  std::string name;
  int score = 0;
  bool isConnected = false;

  sf::RectangleShape paddle;
  PongPlayerDirection direction;
};

using PongClientPlayerList = std::array<PongPlayer, MAX_CONNECTS>;
