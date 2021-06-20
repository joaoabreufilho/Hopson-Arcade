#include "animation.h"

Animation::Animation(unsigned frame_width, unsigned frame_height)
    : kFrameWidth(frame_width), kFrameHeight(frame_height) {}

// Adds a frame...
void Animation::addFrame(unsigned index, sf::Time delay) {
  sf::IntRect bounds;
  bounds.top = 0;
  bounds.height = kFrameHeight;
  bounds.width = kFrameWidth;
  bounds.left = index * kFrameWidth;

  m_frames.emplace_back(bounds, delay);
}

// Returns the current/active frame of the animation
const sf::IntRect& Animation::getFrame() {
  if (m_timer.getElapsedTime() >= m_frames[m_frame_ptr].delay) {
    m_timer.restart();
    m_frame_ptr++;
    if (m_frame_ptr == m_frames.size())
      m_frame_ptr = 0;
  }

  return m_frames[m_frame_ptr].bounds;
}
