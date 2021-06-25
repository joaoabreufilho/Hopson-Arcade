/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file game.h
 * @brief Maincrotolling class for arcade games.
 *
 * - \subpage Subsystem: Arcade
 *
 * \date Jun 2021
 */
/** @addtogroup arcade */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "fps_counter.h"
#include "non_moveable.h"
#include "state_base.h"

/**
 * @class Game
 * @brief Main controlling class of the game.
    Handles state switches and the main loop, as well
    as counting the FPS
 */
class Game : public NonCopyable, public NonMovable {
  struct Action {
    enum class Type {
      kNone,
      kPush,
      kChange,
      kPop,
      kQuit,
    };
    Type type = Type::kNone;
    std::unique_ptr<StateBase> state;
  };

 public:
  Game();

  /**
   * @brief Runs the main loop
   */
  void run();

  template <typename T>
  void initGame();

  void pushState(std::unique_ptr<StateBase> state);
  /**
   * @brief Flags a boolean for the game to pop state
   */
  void popState();
  void exitGame();

  template <typename T, typename... Args>
  void pushState(Args&&... args);

  template <typename T, typename... Args>
  void changeState(Args&&... args);

  /**
   * @brief On tin.
   */
  const sf::RenderWindow& getWindow() const;

  void resizeWindow(unsigned width, unsigned height);

 private:
  /**
   * @brief Handles window events, called every frame.
   */
  void handleEvent();
  /**
   * @brief Tries to pop the current game state.
   */
  void updateStates();
  /**
   * @brief Returns a reference to the current game state.
   */
  StateBase& getCurrentState();

  sf::RenderWindow m_window;
  std::vector<std::unique_ptr<StateBase>> m_states;

  FPSCounter counter;

  Action m_action;
};

template <typename T>
inline void Game::initGame() {
  m_states.push_back(std::make_unique<T>(*this));
}

template <typename T, typename... Args>
inline void Game::pushState(Args&&... args) {
  m_action.type = Action::Type::kPush;
  m_action.state = std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline void Game::changeState(Args&&... args) {
  m_action.type = Action::Type::kChange;
  m_action.state = std::make_unique<T>(std::forward<Args>(args)...);
}
/** @} */