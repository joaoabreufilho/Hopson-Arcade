/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file animation.h
 * @brief Animation frame handler.
 *
 * - \subpage Subsystem: Arcade Util
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_util */
/** @{ */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @class Animation
 * @brief Frame handling.
 */
class Animation {
 public:
  struct Frame {
    Frame(const sf::IntRect& bnds, sf::Time dly) : bounds(bnds), delay(dly) {}

    sf::IntRect bounds;  // The area in a texture of the frame
    sf::Time delay;      // Time delay to next frame
  };

  Animation(unsigned frame_width, unsigned frame_height);

  void addFrame(unsigned index, sf::Time delay);

  const sf::IntRect& getFrame();

 private:
  sf::Clock m_timer;  // Timer for progressing the animation

  std::vector<Frame> m_frames;  // List of animation frames

  unsigned m_frame_ptr = 0;  // The index of the current active frame
  const unsigned kFrameWidth;
  const unsigned kFrameHeight;
};
/** @} */