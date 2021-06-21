#include "world.h"
#include "resource_holder.h"

World::World()
    : m_projectile_renderer(4,
                           8,
                           Projectile::kWidth,
                           Projectile::kHeight,
                           ResourceHolder::get().m_textures.get("si/projectile")),
      m_invaders(*this),
      m_ufo(m_rng) {
  m_explode_shape.setSize({52, 28});
  m_explode_shape.setTexture(
      &ResourceHolder::get().m_textures.get("si/explosion"));

  const int kSectSize = (kInvaderWidth / 4);
  for (int i = 0; i < 4; i++) {
    m_shields.emplace_back(
        float(i * kSectSize + kSectSize / 2 - Shield::kSize / 2));
  }

  m_player_shoot.setBuffer(ResourceHolder::get().m_sound_buffers.get("si/shoot"));
  m_player_shoot.setVolume(25);
}

void World::input() {
  if (m_player.isAlive()) {
    if (m_invaders.areInvadersAlive()) {
      m_player.input();
      playerProjectileInput();
    }
  } else {
    m_player.tryRevive();
  }
}

int World::update(float dt) {
  int score = 0;

  if (m_invaders.areInvadersAlive()) {
    m_player.update(dt);
    if (m_player.isAlive()) {
      m_invaders.tryStepInvaders();
      enemyProjectileFire();

      // pair of score gained and points of collision list
      auto collisionResult = getCollisionResult(dt);
      if (collisionResult.second.size() > 0) {
        score += collisionResult.first;
        for (auto& point : collisionResult.second) {
          m_explosions.emplace_back(point);
        }
      }

      m_ufo.update(dt);
    }

    for (auto itr = m_explosions.begin(); itr != m_explosions.end();) {
      if (itr->isLifeOver())
        itr = m_explosions.erase(itr);
      else
        itr++;
    }
  } else {
    m_invaders.initAddInvader();
    m_projectiles.clear();
    m_explosions.clear();
  }
  return score;
}

const Player& World::getPlayer() const {
  return m_player;
}

bool World::isGameOver() const {
  return m_player.getLives() == -1 || m_is_game_over;
}

// TODO GENERALISE THESE TWO FUNCTIONS VV
void World::playerProjectileInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
      m_player_shot_clock.getElapsedTime().asSeconds() > 0.5f) {
    auto point = m_player.getGunPosition();
    point.y -= Projectile::kHeight;
    point.x -= Projectile::kWidth / 2.0f;
    m_projectiles.emplace_back(point, Projectile::Type::kRectangle,
                               Projectile::Direction::kUp);
    m_player_shot_clock.restart();
    m_player_shoot.play();
  }
}

void World::enemyProjectileFire() {
  if (m_invader_shot_clock.getElapsedTime().asSeconds() >= 0.1 &&
      m_rng.getIntInRange(0, 30) == 2) {
    auto point = m_invaders.getRandomLowestInvaderPoint(m_rng);
    if ((int)point.x == -1)
      return;
    auto type = static_cast<Projectile::Type>(m_rng.getIntInRange(1, 2));
    m_projectiles.emplace_back(point, type, Projectile::Direction::kDown);
    m_invader_shot_clock.restart();
  }
}
// end of to-do

CollisionResult World::getCollisionResult(float dt) {
  auto result = m_invaders.tryCollideWithProjectiles(m_projectiles);
  updateProjectiles(dt, result.second);

  for (auto& projectile : m_projectiles) {
    // Projectile verses sheild collisons
    for (auto& sheild : m_shields) {
      if (sheild.isTouching(projectile)) {
        projectile.destroy();
        result.second.emplace_back(projectile.getPosition());
      }
    }

    // Projectile verses UFO collisons
    if (m_ufo.tryCollideWith(projectile)) {
      result.second.emplace_back(projectile.getPosition());
      result.first += 200;
    }

    // Projectile verses projectile collisions
    for (auto& otherProjectile : m_projectiles) {
      if (otherProjectile.getID() != projectile.getID()) {
        if (otherProjectile.tryCollideWith(projectile)) {
          result.second.emplace_back(projectile.getPosition());
        }
      }
    }
  }

  return result;
}

void World::updateProjectiles(float dt,
                              std::vector<sf::Vector2f>& collisionPoints) {
  for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
    auto& projectile = *itr;
    if (!projectile.isActive()) {
      itr = m_projectiles.erase(itr);
    } else {
      // Test for player getting hit
      if (projectile.tryCollideWith(m_player)) {
        collisionPoints.emplace_back(m_player.getGunPosition());
        m_projectiles.clear();
        return;
      }
      projectile.update(dt);
      itr++;
    }
  }
}

void World::draw(sf::RenderTarget& target) {
  if (m_anim_timer.getElapsedTime().asSeconds() > 0.2) {
    m_projectile_renderer.nextFrame();
    m_anim_timer.restart();
  }

  for (auto& shield : m_shields) {
    shield.draw(target);
  }

  for (auto& proj : m_projectiles) {
    m_projectile_renderer.renderEntity(target, (int)proj.getType(),
                                      proj.getPosition());
  }

  for (auto& exp : m_explosions) {
    m_explode_shape.setPosition(exp.getPosition());
    target.draw(m_explode_shape);
  }

  m_invaders.drawInvaders(target);
  m_player.draw(target);
  m_ufo.draw(target);
}
