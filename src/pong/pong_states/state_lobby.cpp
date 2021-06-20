#include "state_lobby.h"

#include <SFML/Network/Packet.hpp>
#include <iostream>

#include "button.h"
#include "game.h"
#include "label.h"
#include "net.h"
#include "state_error.h"

constexpr unsigned WIDTH = 800;
constexpr unsigned HEIGHT = 600;

StateLobby::StateLobby(Game& game, const std::string& name)
    : StateBase(game, "State Lobby"),
      m_mainMenu(game.getWindow(), HEIGHT / 2 - 100, 400),
      m_playerList({128, 64}, 250),
      m_isHost(true),
      m_name(name),
      m_hostIp(sf::IpAddress::LocalHost)

{
  auto startButton = makeButton();
  startButton->disable();
  startButton->setText("Start");
  startButton->setFunction([&]() {});

  if (!m_server.start(PORT)) {
    m_game_ptr->popState();
  };

  auto exitBtn = makeButton();
  exitBtn->setText("Back");
  exitBtn->setFunction([&]() {
    m_server.stop();
    m_game_ptr->popState();
  });

  m_mainMenu.addWidget(std::move(exitBtn));
  m_startGameButton = m_mainMenu.addWidget(std::move(startButton));
  m_mainMenu.setTitle("Choose Action");

  initPlayerList();
}

StateLobby::StateLobby(Game& game,
                       const std::string& ip,
                       const std::string& name)
    : StateBase(game, "State Lobby"),
      m_mainMenu(game.getWindow(), HEIGHT / 2 - 100, 400),
      m_playerList({128, 64}, 250),
      m_isHost(false),
      m_name(name),
      m_hostIp(ip) {
  auto exitBtn = makeButton();
  exitBtn->setText("Back");
  exitBtn->setFunction([&]() {
    auto packet = makePacket(ToServerCommand::Disconnect);
    packet << m_playerId;
    m_socket.send(packet);
    m_game_ptr->popState();
    m_socket.disconnect();
  });

  m_mainMenu.addWidget(std::move(exitBtn));
  m_mainMenu.setTitle("Waiting for host to start game...");

  initPlayerList();
}

void StateLobby::connectToServer() {
  if (m_socket.connect(sf::IpAddress::LocalHost, PORT) != sf::Socket::Done) {
    m_game_ptr->changeState<StateError>(*m_game_ptr, "Failed to connect to host.");
  }
  m_socket.setBlocking(false);
  m_isConnected = true;
}

void StateLobby::initPlayerList() {
  m_playerList.setTitle("Player List");
  for (auto& label : m_playerNameLabels) {
    auto ref = makeLabel();
    label = (Label*)m_playerList.addWidget(std::move(ref));
  }
}

void StateLobby::handleEvent(sf::Event e) {
  m_mainMenu.handleEvent(e, m_game_ptr->getWindow());
}

void StateLobby::handlePacket(ToClientCommand command, sf::Packet& packet) {
  switch (command) {
    case ToClientCommand::Disconnect:
      m_game_ptr->changeState<StateError>(*m_game_ptr, "Host has disconnected.");
      m_socket.disconnect();
      break;

    case ToClientCommand::PlayerId: {
      packet >> m_playerId;
      auto namePacket = makePacket(ToServerCommand::Name);

      namePacket << m_playerId << m_name;
      m_socket.send(namePacket);
    } break;

    case ToClientCommand::PlayerConnected: {
      m_peerConnections++;
      checkHostStartButton();
      sf::Uint8 id;
      std::string name;
      packet >> id >> name;
      m_playerNameLabels[id]->setLabel(name);
    } break;

    case ToClientCommand::PlayerDisconnected: {
      m_peerConnections--;
      checkHostStartButton();
      sf::Uint8 id;
      packet >> id;
      m_playerNameLabels[id]->setLabel("");
    } break;

    case ToClientCommand::PlayerList: {
      sf::Uint8 count;
      packet >> count;
      m_peerConnections += count;
      for (int i = 0; i < (int)count; i++) {
        sf::Uint8 id;
        std::string name;
        packet >> id >> name;
        std::cout << "PLAYER LIST IDX AND NAME " << (int)id << " >" << name
                  << '\n';
        m_playerNameLabels[id]->setLabel(name);
      }
      std::cout << "GOT PLAYER LIST " << (int)count << std::endl;
    } break;

    default:
      break;
  }
}  // namespace pong

void StateLobby::update([[maybe_unused]] sf::Time deltaTime) {
  if (!m_isConnected) {
    connectToServer();
  }
  if (m_isHost) {
    m_server.update();
  }
  if (m_isConnected) {
    sf::Packet packet;
    if (m_socket.receive(packet) == sf::Socket::Done) {
      sf::Uint8 cmd = 0;
      packet >> cmd;
      auto command = static_cast<ToClientCommand>(cmd);
      handlePacket(command, packet);
    }
  }
}

void StateLobby::checkHostStartButton() {
  if (m_isHost) {
    if (m_peerConnections > 1) {
      m_startGameButton->enable();
    } else {
      m_startGameButton->disable();
    }
  }
}

void StateLobby::render(sf::RenderTarget& renderer) {
  m_playerList.render(renderer);
  m_mainMenu.render(renderer);
}
