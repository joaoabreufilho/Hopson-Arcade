#include "ufo.h"

#include "display_info.h"
#include "resource_holder.h"

constexpr float kWidth = 72;
constexpr float kHeight = 36;
constexpr float kYPos = 45;

UFO::UFO(Random<>& rand)
    : Collidable(kWidth, kHeight), m_rng(rand), m_animation(16, 8) {
  m_sprite.setSize({kWidth, kHeight});
  m_sprite.setPosition((float)kInvaderWidth, kYPos);
  m_sprite.setTexture(&ResourceHolder::get().m_textures.get("si/ufo"));

  for (int i = 0; i < 3; i++) {
    m_animation.addFrame(i, sf::seconds(0.2f));
  }
  m_flying_sound.setBuffer(
      ResourceHolder::get().m_sound_buffers.get("si/ufo_lowpitch"));
  m_flying_sound.setVolume(10);
}

UFO::State UFO::getState() const {
  return m_state;
}

void UFO::update(float dt) {
  switch (m_state) {
    case State::kDestroyed:
      m_state = State::kWaiting;
      break;

    case State::kFlying:
      m_sprite.move(m_vx * dt, 0);
      if (getPosition().x <= -kWidth ||
          getPosition().x >= kInvaderWidth + kWidth) {
        m_state = State::kWaiting;
      }
      if ((int)m_flying_sound.getStatus() != (int)sf::Sound::Status::Playing ||
          m_flying_sound.getPlayingOffset() >= sf::seconds(1.5)) {
        m_flying_sound.setPlayingOffset(sf::seconds(0.2f));
        m_flying_sound.play();
      }
      break;

    case State::kWaiting:
      if (m_rng.getIntInRange(1, 250) == 100) {
        m_state = State::kFlying;
        m_vx = (float)m_rng.getIntInRange(-1, 1) * 200.0f;
        float xPos;
        if (m_vx >= 0) {
          xPos = -kWidth;
        } else {
          xPos = kInvaderWidth;
        }
        m_sprite.setPosition(xPos, kYPos);
      }
      break;
  }
}

void UFO::draw(sf::RenderTarget& window) {
  if (m_state == State::kFlying) {
    m_sprite.setTextureRect(m_animation.getFrame());
    window.draw(m_sprite);
  }
}

const sf::Vector2f& UFO::getPosition() const {
  return m_sprite.getPosition();
}

void UFO::onCollide([[maybe_unused]] Collidable& other) {
  m_state = State::kDestroyed;
  m_sprite.setPosition(
      -1000,
      0);  // Move offscreen so it cannot be collided with projectiles
}
