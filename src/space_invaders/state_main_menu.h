#pragma once

#include "stack_menu.h"
#include "starry_background.h"
#include "state_base.h"
#include "random.h"

class StateMainMenu : public StateBase {
 public:
  StateMainMenu(Game& game);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time deltaTime) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  StackMenu m_mainMenu;
  sf::RectangleShape m_banner;

  StarryBackground m_background;
};