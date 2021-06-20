/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file toggle_key.h
 * @brief Key press handler.
 *
 * - \subpage Subsystem: Arcade Resources
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_resources */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>
/**
 * @class ToggleKey
 * @brief Key press handler.
 */
class ToggleKey {
 public:
  ToggleKey(sf::Keyboard::Key);

  bool isKeyPressed();

 private:
  sf::Keyboard::Key m_key;
  sf::Clock m_delay_timer;
};
/** @} */