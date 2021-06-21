/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file pong_server.h
 * @brief Server handler.
 *
 * - \subpage Subsystem: Pong Server
 *
 * \date Jun 2021
 */
/** @addtogroup pong_server */
/** @{ */
#pragma once

#include "net.h"

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <array>
#include <cstdint>

/**
 * @brief Connection struct.
 */
struct Connection {
  sf::Uint8 id = 0;
  sf::TcpSocket socket;
  bool isConnected = false;

  std::string name;
};

/**
 * @class PongServer
 * @brief Pong Server Handler.
 */
class PongServer {
 public:
  enum class State {
    kLobby,
    kInGame,
  };
  State state = State::kLobby;

  bool start(uint16_t port);
  void stop();

  void update();

 private:
  void handlePacket(ToServerCommand command, sf::Packet& packet);
  void broadcast(sf::Packet& packet);

  std::array<Connection, kMaxConnects> m_connections;
  sf::TcpListener m_tcp_listener;

  int m_current_connections = 0;
};
/** @} */