/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file animation_renderer.h
 * @brief Entities renderization handler.
 *
 * - \subpage Subsystem: Space Invaders
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>

/**
 * @class StateLobby
 * @brief Utility class for rendering a large number of entites which share
 *  the same animation
 */
class AnimationRenderer {
 public:
  AnimationRenderer(int frame_width,
                    int frame_height,
                    float entity_width,
                    float entity_height,
                    const sf::Texture& sprite_sheet);

  // Changes to the next frame
  void nextFrame();

  // Renders a single entity, using the current Animation frame
  void renderEntity(sf::RenderTarget& renderer,
                    int type,
                    const sf::Vector2f& position);

 private:
  sf::RectangleShape m_entity;
  int m_current_frame;
  const int m_frame_width;
  const int m_frame_height;
};
/** @} */