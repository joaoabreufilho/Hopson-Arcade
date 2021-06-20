#include "resource_holder.h"

ResourceHolder& ResourceHolder::get() {
  static ResourceHolder holder;
  return holder;
}

ResourceHolder::ResourceHolder()
    : m_fonts("fonts", "ttf"),
      m_textures("txrs", "png"),
      m_sound_buffers("sfx", "ogg") {}
