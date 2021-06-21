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

const uint16_t kPort = 52324;
const int kMaxConnects = 4;

/**
 * @brief Command to server.
 */
enum class ToServerCommand : sf::Uint8 {
  kDisconnect,
  kName,
};

/**
 * @brief Command to client.
 */
enum class ToClientCommand : sf::Uint8 {
  // Just the enum
  kDisconnect,
  // u8: player id
  kPlayerId,
  // u8: player id
  // string: name
  kPlayerConnected,
  // u8: player id
  kPlayerDisconnected,
  // u8: count
  // <u8, sting>[count]: id, name
  kPlayerList
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