/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file state_lobby.h
 * @brief Pong lobby state handler.
 *
 * - \subpage Subsystem: Pong Server
 *
 * \date Jun 2021
 */
/** @addtogroup pong_states */
/** @{ */
#pragma once

#include "net.h"
#include "pong_server.h"
#include "stack_menu.h"
#include "state_base.h"

class Widget;
class Label;

/**
 * @class StateLobby
 * @brief Lobby input and state handler.
 */
class StateLobby : public StateBase {
 public:
  StateLobby(Game& game, const std::string& name);
  StateLobby(Game& game, const std::string& ip, const std::string& name);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time deltaTime) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  void connectToServer();
  void initPlayerList();

  void checkHostStartButton();

  void handlePacket(ToClientCommand command, sf::Packet& packet);

  PongServer m_server;
  sf::TcpSocket m_socket;

  StackMenu m_mainMenu;
  StackMenu m_playerList;

  Widget* m_startGameButton = nullptr;

  std::array<Label*, MAX_CONNECTS> m_playerNameLabels;

  bool m_isHost;
  bool m_isConnected = false;

  std::string m_name;
  sf::IpAddress m_hostIp;

  sf::Uint8 m_playerId;

  int m_peerConnections = 0;
};
/** @} */