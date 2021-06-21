#include "state_lobby.h"

#include <SFML/Network/Packet.hpp>
#include <iostream>

#include "button.h"
#include "game.h"
#include "label.h"
#include "net.h"
#include "state_error.h"

constexpr unsigned kWidth = 800;
constexpr unsigned kHeight = 600;

StateLobby::StateLobby(Game& game, const std::string& name)
    : StateBase(game, "State Lobby"),
      m_main_menu(game.getWindow(), kHeight / 2 - 100, 400),
      m_player_list({128, 64}, 250),
      m_is_host(true),
      m_name(name),
      m_host_ip(sf::IpAddress::LocalHost)

{
  auto startButton = makeButton();
  startButton->disable();
  startButton->setText("Start");
  startButton->setFunction([&]() {});

  if (!m_server.start(kPort)) {
    m_game_ptr->popState();
  };

  auto exitBtn = makeButton();
  exitBtn->setText("Back");
  exitBtn->setFunction([&]() {
    m_server.stop();
    m_game_ptr->popState();
  });

  m_main_menu.addWidget(std::move(exitBtn));
  m_start_game_button_ptr = m_main_menu.addWidget(std::move(startButton));
  m_main_menu.setTitle("Choose Action");

  initPlayerList();
}

StateLobby::StateLobby(Game& game,
                       const std::string& ip,
                       const std::string& name)
    : StateBase(game, "State Lobby"),
      m_main_menu(game.getWindow(), kHeight / 2 - 100, 400),
      m_player_list({128, 64}, 250),
      m_is_host(false),
      m_name(name),
      m_host_ip(ip) {
  auto exitBtn = makeButton();
  exitBtn->setText("Back");
  exitBtn->setFunction([&]() {
    auto packet = makePacket(ToServerCommand::kDisconnect);
    packet << m_player_id;
    m_socket.send(packet);
    m_game_ptr->popState();
    m_socket.disconnect();
  });

  m_main_menu.addWidget(std::move(exitBtn));
  m_main_menu.setTitle("Waiting for host to start game...");

  initPlayerList();
}

void StateLobby::connectToServer() {
  if (m_socket.connect(sf::IpAddress::LocalHost, kPort) != sf::Socket::Done) {
    m_game_ptr->changeState<StateError>(*m_game_ptr, "Failed to connect to host.");
  }
  m_socket.setBlocking(false);
  m_is_connected = true;
}

void StateLobby::initPlayerList() {
  m_player_list.setTitle("Player List");
  for (auto& label : m_player_name_labels) {
    auto ref = makeLabel();
    label = (Label*)m_player_list.addWidget(std::move(ref));
  }
}

void StateLobby::handleEvent(sf::Event e) {
  m_main_menu.handleEvent(e, m_game_ptr->getWindow());
}

void StateLobby::handlePacket(ToClientCommand command, sf::Packet& packet) {
  switch (command) {
    case ToClientCommand::kDisconnect:
      m_game_ptr->changeState<StateError>(*m_game_ptr, "Host has disconnected.");
      m_socket.disconnect();
      break;

    case ToClientCommand::kPlayerId: {
      packet >> m_player_id;
      auto namePacket = makePacket(ToServerCommand::kName);

      namePacket << m_player_id << m_name;
      m_socket.send(namePacket);
    } break;

    case ToClientCommand::kPlayerConnected: {
      m_peer_connections++;
      checkHostStartButton();
      sf::Uint8 id;
      std::string name;
      packet >> id >> name;
      m_player_name_labels[id]->setLabel(name);
    } break;

    case ToClientCommand::kPlayerDisconnected: {
      m_peer_connections--;
      checkHostStartButton();
      sf::Uint8 id;
      packet >> id;
      m_player_name_labels[id]->setLabel("");
    } break;

    case ToClientCommand::kPlayerList: {
      sf::Uint8 count;
      packet >> count;
      m_peer_connections += count;
      for (int i = 0; i < (int)count; i++) {
        sf::Uint8 id;
        std::string name;
        packet >> id >> name;
        std::cout << "PLAYER LIST IDX AND NAME " << (int)id << " >" << name
                  << '\n';
        m_player_name_labels[id]->setLabel(name);
      }
      std::cout << "GOT PLAYER LIST " << (int)count << std::endl;
    } break;

    default:
      break;
  }
}  // namespace pong

void StateLobby::update([[maybe_unused]] sf::Time deltaTime) {
  if (!m_is_connected) {
    connectToServer();
  }
  if (m_is_host) {
    m_server.update();
  }
  if (m_is_connected) {
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
  if (m_is_host) {
    if (m_peer_connections > 1) {
      m_start_game_button_ptr->enable();
    } else {
      m_start_game_button_ptr->disable();
    }
  }
}

void StateLobby::render(sf::RenderTarget& renderer) {
  m_player_list.render(renderer);
  m_main_menu.render(renderer);
}
