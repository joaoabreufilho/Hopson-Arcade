#include "invader.h"

Invader::Invader(const sf::Vector2f& initialLocation, Type type)
    : Collidable(kWidth, kHeight),
      m_initial_position(initialLocation),
      m_location(initialLocation),
      m_type(type) {}

void Invader::move(float x, float y) {
  m_location += {x, y};
}

const sf::Vector2f& Invader::getPosition() const {
  return m_location;
}

bool Invader::isAlive() const {
  return m_is_alive;
}

Invader::Type Invader::getType() const {
  return m_type;
}

void Invader::onCollide([[maybe_unused]] Collidable& other) {
  m_is_alive = false;
}
