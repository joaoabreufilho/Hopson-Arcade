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
  void update(sf::Time delta_time) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  void connectToServer();
  void initPlayerList();

  void checkHostStartButton();

  void handlePacket(ToClientCommand command, sf::Packet& packet);

  PongServer m_server;
  sf::TcpSocket m_socket;

  StackMenu m_main_menu;
  StackMenu m_player_list;

  Widget* m_start_game_button_ptr = nullptr;

  std::array<Label*, kMaxConnects> m_player_name_labels;

  bool m_is_host;
  bool m_is_connected = false;

  std::string m_name;
  sf::IpAddress m_host_ip;

  sf::Uint8 m_player_id;

  int m_peer_connections = 0;
};
/** @} */