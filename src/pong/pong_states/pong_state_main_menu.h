/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file pong_state_main_menu.h
 * @brief Main menu pong state.
 *
 * - \subpage Subsystem: Pong Server
 *
 * \date Jun 2021
 */
/** @addtogroup pong_states */
/** @{ */
#pragma once

#include "stack_menu.h"
#include "state_base.h"

/**
 * @class PongStateMainMenu
 * @brief Pong state main menu.
 */
class PongStateMainMenu : public StateBase {
 public:
  PongStateMainMenu(Game& game);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time deltaTime) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  StackMenu m_main_menu;
  StackMenu m_join_menu;
  StackMenu m_create_lobby_menu;
  StackMenu* m_active_menu_ptr = nullptr;
  sf::RectangleShape m_banner;

  std::string m_join_ip = "192.168.0.19";
  std::string m_name;
};
/** @} */