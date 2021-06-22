#include "animation_renderer.h"

AnimationRenderer::AnimationRenderer(int frame_width,
                                     int frame_height,
                                     float entity_width,
                                     float entity_height,
                                     const sf::Texture& sprite_sheet)
    : m_frame_width(frame_width), m_frame_height(frame_height) {
  m_entity.setSize({entity_width, entity_height});
  m_entity.setTexture(&sprite_sheet);
}

void AnimationRenderer::nextFrame() {
  m_current_frame++;
}

void AnimationRenderer::renderEntity(sf::RenderTarget& renderer,
                                     int type,
                                     const sf::Vector2f& position) {
  // Calculate texture coords
  int texLeft = (m_current_frame % 2) * m_frame_width;
  int texTop = (type * m_frame_height);

  // Reposition and draw sprite
  m_entity.setPosition(position);
  m_entity.setTextureRect({texLeft, texTop, m_frame_width, m_frame_height});
  renderer.draw(m_entity);
}
