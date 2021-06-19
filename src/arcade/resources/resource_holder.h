#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "non_copyable.h"
#include "non_moveable.h"
#include "resource_manager.h"

class ResourceHolder : public NonCopyable, public NonMovable {
 public:
  static ResourceHolder& get();

  ResourceManager<sf::Font> fonts;
  ResourceManager<sf::Texture> textures;
  ResourceManager<sf::SoundBuffer> soundBuffers;

 private:
  ResourceHolder();
};
