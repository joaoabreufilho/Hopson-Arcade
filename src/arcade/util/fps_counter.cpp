#include "fps_counter.h"

#include <iostream>

#include "resource_holder.h"

FPSCounter::FPSCounter() {
  m_text.move(0, 0);
  m_text.setOutlineColor(sf::Color::Black);
  m_text.setFillColor({255, 255, 255});
  m_text.setOutlineThickness(2);
  m_text.setFont(ResourceHolder::get().m_fonts.get("arcade"));
  m_text.setCharacterSize(15);
}

void FPSCounter::update() {
  m_frame_count++;

  if (m_delay_timer.getElapsedTime().asSeconds() > 0.2) {
    m_fps = m_frame_count / m_fps_timer.restart().asSeconds();
    m_frame_count = 0;
    m_delay_timer.restart();
  }
}

void FPSCounter::draw(sf::RenderTarget& renderer) {
  m_text.setString("FPS " + std::to_string((int)m_fps));
  renderer.draw(m_text);
}
