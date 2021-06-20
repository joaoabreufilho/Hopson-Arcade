/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file fps_counter.h
 * @brief fps counter handler.
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
 * @class FPSCounter
 * @brief Frame update handler.
 */
class FPSCounter {
 public:
  FPSCounter();

  void update();

  void draw(sf::RenderTarget& renderer);

 private:
  sf::Text m_text;
  sf::Font m_font;

  sf::Clock m_delay_timer;
  sf::Clock m_fpsTimer;

  float m_fps = 0;

  int m_frameCount = 0;
};
/** @} */