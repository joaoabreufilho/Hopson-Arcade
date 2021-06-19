#pragma once

#include "net.h"
#include "pong_server.h"
#include "stack_menu.h"
#include "state_base.h"

class Widget;
class Label;

class StateLobby : public StateBase {
 public:
  StateLobby(Game& game, const std::string& name);
  StateLobby(Game& game,
             const std::string& ip,
             const std::string& name);

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
