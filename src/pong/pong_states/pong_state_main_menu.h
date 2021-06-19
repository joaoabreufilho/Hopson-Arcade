#pragma once

#include "stack_menu.h"
#include "state_base.h"

class PongStateMainMenu : public StateBase {
 public:
  PongStateMainMenu(Game& game);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time deltaTime) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  StackMenu m_mainMenu;
  StackMenu m_joinMenu;
  StackMenu m_createLobbyMenu;
  StackMenu* mp_activeMenu = nullptr;
  sf::RectangleShape m_banner;

  std::string m_joinIp = "192.168.0.19";
  std::string m_name;
};
