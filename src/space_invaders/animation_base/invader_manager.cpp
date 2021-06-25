#include "invader_manager.h"

#include <iostream>

#include <resource_holder.h>
#include "world.h"

const int kMaxInvaders = 55;

InvaderManager::InvaderManager(World& world)
    : m_step_gap(sf::seconds(0.5f)),
      m_world(world),
      m_invader_renderer(
          12,
          8,
          Invader::kWidth,
          Invader::kHeight,
          ResourceHolder::get().m_textures.get("si/invaders")) {
  // Layout of the invaders
  Invader::Type types[] = {Invader::Type::kSquid, Invader::Type::kCrab,
                           Invader::Type::kCrab, Invader::Type::kOctopus,
                           Invader::Type::kOctopus};
  // Add invaders into the std::vector
  const int kGap = 10;
  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 11; x++) {
      // calcuate position for invader
      float invaderX = x * Invader::kWidth + (kGap * x * 3) + Invader::kWidth;
      float invaderY = y * Invader::kHeight + (kGap * y) + Invader::kHeight * 4;
      m_invaders.emplace_back(sf::Vector2f{invaderX, invaderY}, types[y]);
    }
  }

  // load sounds
  for (int i = 0; i < 4; i++) {
    m_step_sounds[i].setBuffer(ResourceHolder::get().m_sound_buffers.get(
        "si/fastinvader" + std::to_string(i + 1)));
  }
  m_invader_killed_sound.setBuffer(
      ResourceHolder::get().m_sound_buffers.get("si/invaderkilled"));
}

void InvaderManager::tryStepInvaders() {
  // Only step if clock is over timer
  if (m_step_timer.getElapsedTime() > m_step_gap) {
    m_invader_renderer.nextFrame();
    // Calculate amount to step
    bool moveDown = false;
    float step = m_is_moving_left ? -10.0f : 10.0f;
    if (m_move_down) {
      step *= -1;
    }
    m_step_sounds[m_ticks++ % 4].play();

    // Move the invaders
    for (auto& invader : m_invaders) {
      if (!invader.isAlive())
        continue;
      invader.move(step, 0.0f);
      if (m_move_down) {
        invader.move(0, Invader::kHeight / 2.0f);
      } else if (!moveDown) {
        // Check invader position to see if all should move down
        moveDown = testInvaderPosition(invader);
      }
    }

    if (m_move_down)
      m_is_moving_left = !m_is_moving_left;
    m_move_down = moveDown;
    m_step_timer.restart();
  }
}

void InvaderManager::drawInvaders(sf::RenderTarget& target) {
  for (auto& invader : m_invaders) {
    if (!invader.isAlive())
      continue;
    m_invader_renderer.renderEntity(target, (int)invader.getType(),
                                   invader.getPosition());
  }
}

CollisionResult InvaderManager::tryCollideWithProjectiles(
    std::vector<Projectile>& projectiles) {
  CollisionResult result;
  std::vector<sf::Vector2f> collisionPoints;
  for (auto& projectile : projectiles) {
    for (auto& invader : m_invaders) {
      if (!invader.isAlive() || !projectile.isActive())
        continue;
      if (projectile.tryCollideWith(invader)) {
        m_alive_invaders--;
        m_invader_killed_sound.play();
        if (m_alive_invaders == 0) {
          m_has_all_invaders_been_added = false;
        }
        result.second.emplace_back(invader.getPosition());
        result.first += ((int)invader.getType() + 1) * 100;
        updateStepDelay();
      }
    }
  }
  return result;
}

sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(
    Random<>& random) {
  if (m_alive_invaders == 0)
    return {-1, -1};
  // Keep looping until an invader is found
  while (true) {
    auto invaderColumn = random.getIntInRange(0, 10);
    for (int y = 4; y >= 0; y--) {
      int index = y * 11 + invaderColumn;
      auto& invader = m_invaders.at(index);
      if (invader.isAlive()) {
        return {// transform to below the invader's center
                invader.getPosition().x + Invader::kWidth / 2,
                invader.getPosition().y + Invader::kHeight + 5};
      }
    }
  }
}

int InvaderManager::getAliveInvadersCount() const {
  return m_alive_invaders;
}

// Adds invaders to scene 1 at a time
void InvaderManager::initAddInvader() {
  static sf::Clock delay;
  if (delay.getElapsedTime().asSeconds() > 0.02) {
    m_invaders.at(m_init_y * 11 + m_init_x).makeAlive();
    m_alive_invaders++;
    m_init_x++;
    if (m_init_x == 11) {
      m_init_x = 0;
      m_init_y--;
    }
    delay.restart();
  }

  if (m_alive_invaders == kMaxInvaders) {
    m_has_all_invaders_been_added = true;
    m_init_x = 0;
    m_init_y = 4;
    updateStepDelay();
  }
}

bool InvaderManager::areInvadersAlive() const {
  return m_has_all_invaders_been_added;
}

void InvaderManager::updateStepDelay() {
  m_step_gap = sf::seconds((float)m_alive_invaders / 90.0f);
}

bool InvaderManager::testInvaderPosition(const Invader& invader) const {
  if (invader.getPosition().y > kInvadersHeight - 150) {
    m_world.setGameIsOver();
  }
  return (invader.getPosition().x < 15 &&
          m_is_moving_left) ||  // Check invader left
         (invader.getPosition().x + Invader::kWidth > kInvaderWidth - 15 &&
          !m_is_moving_left);  // Check invader right
}
