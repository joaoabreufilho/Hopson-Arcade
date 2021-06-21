/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file net.h
 * @brief sf conections utiliies.
 *
 * - \subpage Subsystem: Pong Server
 *
 * \date Jun 2021
 */
/** @addtogroup pong_server */
/** @{ */
#pragma once

#include <SFML/Network/Packet.hpp>
#include <array>

const uint16_t PORT = 52324;
const int MAX_CONNECTS = 4;

/**
 * @brief Command to server.
 */
enum class ToServerCommand : sf::Uint8 {
  Disconnect,
  Name,
};

/**
 * @brief Command to client.
 */
enum class ToClientCommand : sf::Uint8 {
  // Just the enum
  Disconnect,

  // u8: player id
  PlayerId,

  // u8: player id
  // string: name
  PlayerConnected,

  // u8: player id
  PlayerDisconnected,

  // u8: count
  // <u8, sting>[count]: id, name
  PlayerList
};

/**
 * @brief Packet template.
 */
template <typename T>
sf::Packet makePacket(T commandToSend) {
  sf::Uint8 command = static_cast<sf::Uint8>(commandToSend);
  sf::Packet packet;
  packet << command;
  return packet;
}

/** @} */