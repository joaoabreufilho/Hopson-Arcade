#include "state_error.h"

#include <SFML/Network/Packet.hpp>

#include "button.h"
#include "game.h"
#include "net.h"

constexpr unsigned WIDTH = 800;
constexpr unsigned HEIGHT = 600;

StateError::StateError(Game& game, const std::string& message)
    : StateBase(game, "State Error"),
      m_messageMenu(game.getWindow(), HEIGHT / 2 - 100, 400) {
  auto exit = makeButton();
  exit->setText("Exit");
  exit->setFunction([&]() { game.popState(); });

  m_messageMenu.addWidget(std::move(exit));
  m_messageMenu.setTitle(message);
}

void StateError::handleEvent(sf::Event e) {
  m_messageMenu.handleEvent(e, m_pGame->getWindow());
}

void StateError::update([[maybe_unused]] sf::Time deltaTime) {}

void StateError::render(sf::RenderTarget& renderer) {
  m_messageMenu.render(renderer);
}