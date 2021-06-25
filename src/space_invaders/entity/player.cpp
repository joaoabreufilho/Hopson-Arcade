#include "player.h"
#include "display_info.h"
#include "resource_holder.h"

constexpr float kBaseY = (float)kInvadersHeight - 40.0f;

Player::Player() : Collidable(44, 32), m_death_animation(11, 8) {
  m_sprite.setSize({44, 32});
  m_sprite.setPosition({kInvaderWidth / 2, kBaseY});
  m_sprite.setTexture(&ResourceHolder::get().m_textures.get("si/player"));
  m_sprite.setTextureRect({0, 0, 11, 8});

  for (int i = 0; i < 20; i++) {
    m_death_animation.addFrame(((i % 2) + 1), sf::seconds(0.1f));
  }

  m_death_sound.setBuffer(
      ResourceHolder::get().m_sound_buffers.get("si/explosion"));
}

void Player::restart() {
  m_velocity *= 0.0f;
  m_sprite.setTextureRect({0, 0, 11, 8});
  m_is_alive = true;
  m_lives_left--;
  m_sprite.setPosition({kInvaderWidth / 2, kBaseY});
}

void Player::input() {
  using Key = sf::Keyboard::Key;
  auto keyDown = [](sf::Keyboard::Key k) {
    return sf::Keyboard::isKeyPressed(k);
  };

  float speed = 20;
  if (keyDown(Key::A)) {
    m_velocity.x -= speed;
  } else if (keyDown(Key::D)) {
    m_velocity.x += speed;
  }
}

void Player::update(float dt) {
  if (m_is_alive) {
    auto w = m_sprite.getGlobalBounds().width;
    m_sprite.move(m_velocity * dt);
    m_velocity *= 0.95f;
    if (m_sprite.getPosition().x <= 0) {
      m_velocity.x = 1.0f;
      m_sprite.setPosition(1.0f, kBaseY);
    } else if (m_sprite.getPosition().x + w >= kInvaderWidth) {
      m_velocity.x = -1.0f;
      m_sprite.setPosition(kInvaderWidth - 1.0f - w, kBaseY);
    }
  }
}

void Player::draw(sf::RenderTarget& target) {
  if (!m_is_alive) {
    m_sprite.setTextureRect(m_death_animation.getFrame());
  }
  if (m_lives_left >= 0) {
    target.draw(m_sprite);
  }
}

sf::Vector2f Player::getGunPosition() const {
  return {m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
          m_sprite.getPosition().y};
}

const sf::Vector2f& Player::getPosition() const {
  return m_sprite.getPosition();
}

void Player::onCollide([[maybe_unused]] Collidable& other) {
  m_is_alive = false;
  m_death_timer.restart();
  m_death_sound.play();
}

int Player::getLives() const {
  return m_lives_left;
}

bool Player::isAlive() const {
  return m_is_alive;
}

void Player::tryRevive() {
  if (m_death_timer.getElapsedTime().asSeconds() >= 1.5f) {
    restart();
  }
}
