#include "starry_background.h"

#include "display_info.h"

StarryBackground::StarryBackground() {
  for (int i = 0; i < 500; i++) {
    sf::Vertex star;
    giveStarRandomStartLocation(star);
    star.position.y -= kInvadersHeight;
    m_stars.push_back(star);
  }
}

void StarryBackground::update(float dt) {
  for (auto& star : m_stars) {
    star.position.y -= 250 * dt;
    if (star.position.y <= 0) {
      giveStarRandomStartLocation(star);
    }
  }
}

void StarryBackground::draw(sf::RenderTarget& renderer) {
  renderer.draw(m_stars.data(), m_stars.size(), sf::Points);
}

void StarryBackground::giveStarRandomStartLocation(sf::Vertex& star) {
  star.position = {m_rng.getFloatInRange(0, (float)kInvaderWidth),
                   m_rng.getFloatInRange((float)kInvadersHeight,
                                         (float)kInvadersHeight * 2.0f)};
}
