/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file keyboard.h
 * @brief keyboard state handler.
 *
 * - \subpage Subsystem: Arcade Input
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_input */
/** @{ */
#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <array>

/**
 * @class Keyboard
 * @brief Holds the state of the keyboard
 */

class Keyboard {
 public:
  Keyboard();

  /**
   * @brief Updates the state of the keyboard. Must be called every frame
   * in the event loop.
   *
   * @param e The event to check key events for
   */
  void update(sf::Event e);

  /**
   * @brief Check if a key is currently down
   *
   * @param key The key to check
   * @return true The key is down
   * @return false The key is up
   */
  bool isKeyDown(sf::Keyboard::Key key) const;

  /**
   * @brief Check if a key was recently released
   *
   * @param key The key to check if it was released
   * @return true The key was recently released
   * @return false The key was not recently released
   */
  bool keyReleased(sf::Keyboard::Key key) const;

 private:
  std::array<bool, sf::Keyboard::KeyCount> m_keys;
  sf::Keyboard::Key m_recently_released;
};
/** @} */