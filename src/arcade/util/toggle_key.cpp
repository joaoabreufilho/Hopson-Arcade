#include "toggle_key.h"

ToggleKey::ToggleKey(sf::Keyboard::Key key) : m_key(key) {}

bool ToggleKey::isKeyPressed() {
  if (m_delay_timer.getElapsedTime().asSeconds() > 0.2) {
    if (sf::Keyboard::isKeyPressed(m_key)) {
      m_delay_timer.restart();
      return true;
    }
  }
  return false;
}
