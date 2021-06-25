/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file state_main_menu.h
 * @brief Main menu state manager.
 *
 * - \subpage Subsystem: Space Invaders States
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_states */
/** @{ */
#pragma once

#include "random.h"
#include "stack_menu.h"
#include "starry_background.h"
#include "state_base.h"

/**
 * @class StateMainMenu
 * @brief Main menu state manager.
 */
class StateMainMenu : public StateBase {
 public:
  StateMainMenu(Game& game);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time delta_time) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  StackMenu m_main_menu;
  sf::RectangleShape m_banner;

  StarryBackground m_background;
};
/** @} */