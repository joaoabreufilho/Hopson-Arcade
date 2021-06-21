/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file resource_holder.h
 * @brief Resource buffering handler.
 *
 * - \subpage Subsystem: Arcade Resources
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_resources */
/** @{ */
#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "non_copyable.h"
#include "non_moveable.h"
#include "resource_manager.h"

/**
 * @class ResourceHolder
 * @brief Resources buffering handler.
 */
class ResourceHolder : public NonCopyable, public NonMovable {
 public:
  static ResourceHolder& get();

  ResourceManager<sf::Font> m_fonts;
  ResourceManager<sf::Texture> m_textures;
  ResourceManager<sf::SoundBuffer> m_sound_buffers;

 private:
  ResourceHolder();
};
/** @} */