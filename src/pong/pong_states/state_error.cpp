#include "state_error.h"

#include <SFML/Network/Packet.hpp>

#include "button.h"
#include "game.h"
#include "net.h"

constexpr unsigned kWidth = 800;
constexpr unsigned kHeight = 600;

StateError::StateError(Game& game, const std::string& message)
    : StateBase(game, "State Error"),
      m_message_menu(game.getWindow(), kHeight / 2 - 100, 400) {
  auto exit = makeButton();
  exit->setText("Exit");
  exit->setFunction([&]() { game.popState(); });

  m_message_menu.addWidget(std::move(exit));
  m_message_menu.setTitle(message);
}

void StateError::handleEvent(sf::Event e) {
  m_message_menu.handleEvent(e, m_game_ptr->getWindow());
}

void StateError::update([[maybe_unused]] sf::Time deltaTime) {}

void StateError::render(sf::RenderTarget& renderer) {
  m_message_menu.render(renderer);
}