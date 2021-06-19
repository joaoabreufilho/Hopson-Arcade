#pragma once

#include "stack_menu.h"
#include "state_base.h"

class Widget;

class StateError : public StateBase {
 public:
  StateError(Game& game, const std::string& message);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time deltaTime) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  StackMenu m_messageMenu;
};
