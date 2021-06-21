/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file state_error.h
 * @brief Pong state error handler.
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

class Widget;

/**
 * @class StateError
 * @brief Pong state error handler.
 */
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
/** @} */