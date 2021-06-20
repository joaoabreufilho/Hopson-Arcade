/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created using C++17 and
 * SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file state_base.h
 * @brief Base event state class for arcade games.
 *
 * - \subpage Subsystem: Arcade
 *
 * \date Jun 2021
 */
/** @addtogroup arcade */
/** @{ */

#pragma once

#include <SFML/Graphics.hpp>

#include "non_copyable.h"

class Game;

/**
 * @class StateBase
 * @brief This class centralizes the system resouces and communication with the
 * application.
 */
class StateBase : public NonCopyable {
 public:
  StateBase(Game& game, const char* name);

  StateBase(Game& game,
            const char* name,
            unsigned resize_window_width,
            unsigned resize_window_height);

  virtual ~StateBase() = default;

  virtual void onOpen() {}
  virtual void handleEvent([[maybe_unused]] sf::Event e) {}
  virtual void handleInput() {}
  virtual void update([[maybe_unused]] sf::Time delta_time) {}
  virtual void fixedUpdate([[maybe_unused]] sf::Time delta_time) {}
  virtual void render(sf::RenderTarget& renderer) = 0;

  const std::string& getName() { return m_name; }

 protected:
  Game* m_game_ptr;
  std::string m_name;
};
/** @} */