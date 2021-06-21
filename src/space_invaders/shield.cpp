#include "shield.h"

#include "display_info.h"
#include "projectile.h"
#include "random.h"

#include <iostream>

Shield::Shield(float x)
    : Collidable((float)kSize, (float)kSize),
      m_position(x, kInvadersHeight - 200) {
  using Sty = SectorStyle;
  for (float sy = 0; sy < 4; sy++) {
    for (float sx = 0; sx < 4; sx++) {
      Sty style = Sty::kSquare;
      int xP = (int)sx;
      int yP = (int)sy;
      if (xP == 0 && yP == 0)
        style = Sty::kSlopeUp;
      if (xP == 3 && yP == 0)
        style = Sty::kSlopeDown;
      if (xP == 1 && yP == 3)
        style = Sty::kSlopeUnderUp;
      if (xP == 2 && yP == 3)
        style = Sty::kSlopeUnderDown;

      m_sections.emplace_back(x + sx * kSectSize, m_position.y + sy * kSectSize,
                              style);
    }
  }
}

void Shield::draw(sf::RenderTarget& target) {
  for (auto& sect : m_sections) {
    sect.draw(target);
  }
}

const sf::Vector2f& Shield::getPosition() const {
  return m_position;
}

Shield::ShieldSection& Shield::getSection(int x, int y) {
  return m_sections[y * 4 + x];
}

void Shield::destroyPoint(float relX, float relY) {
  // Test for out of bounds
  if (relX < 0 || relX >= kSize || relY < 0 || relY >= kSize)
    return;

  // Get section this is inside of
  int xIndex = (int)relX / kSectSize;
  int yIndex = (int)relY / kSectSize;
  auto& section = getSection(xIndex, yIndex);
  auto& sectionPos = section.getPosition();

  // Transform to find the pixel coordinate
  float sectionTopLeftX = sectionPos.x - m_position.x;
  float sectionTopLeftY = sectionPos.y - m_position.y;
  float pixelX = relX - sectionTopLeftX;
  float pixelY = relY - sectionTopLeftY;

  // DESTROY
  section.destroyArea((int)pixelX, (int)pixelY);
}

bool Shield::isTouching(const Projectile& projectile) {
  static Random<> rand;
  if (projectile.getBox().intersects(getBox())) {
    for (auto& sector : m_sections) {
      auto result = sector.isTouching(projectile);
      if ((int)result.x == -1)
        continue;
      else {  // This means the projectile is touching the shield

        // Get coordinate of collision point relative to top left of
        // sheild
        result.x -= m_position.x;
        result.y -= m_position.y;

        // Destory around point of collision
        for (int y = -3; y < 3; y++) {
          for (int x = -3; x < 3; x++) {
            float newRelativeX = result.x + x * 2;
            float newRelativeY = result.y + y * 2;
            destroyPoint(newRelativeX, newRelativeY);
          }
        }

        // blast damge
        float radius = 12.0f;
        for (int i = 0; i < 35; i++) {
          float newRelativeX = result.x + rand.getFloatInRange(-radius, radius);
          float newRelativeY = result.y + rand.getFloatInRange(-radius, radius);
          destroyPoint(newRelativeX, newRelativeY);
        }
        return true;
      }
    }
  }
  return false;
}

Shield::ShieldSection::ShieldSection(float tlX, float tlY, SectorStyle style)
    : Collidable((float)kSectSize, (float)kSectSize), m_position({tlX, tlY}) {
  for (float y = 0; y < kSectSize; y++) {
    for (float x = 0; x < kSectSize; x++) {
      sf::Vertex pixel;
      pixel.color = sf::Color::Green;
      pixel.position = {x + tlX, y + tlY};
      calculatePixelCoord((int)x, (int)y, pixel, style);
    }
  }
}

void Shield::ShieldSection::draw(sf::RenderTarget& target) {
  target.draw(m_pixels.data(), m_pixels.size(), sf::Points);
}

const sf::Vector2f& Shield::ShieldSection::getPosition() const {
  return m_position;
}

sf::Vector2f Shield::ShieldSection::isTouching(const Projectile& other) {
  for (auto& px : m_pixels) {
    if (other.getBox().contains(px.position) && px.color == sf::Color::Green) {
      return px.position;
    }
  }
  return {-1, -1};
}

// Blacks out an area around the inputted point
void Shield::ShieldSection::destroyArea(int x, int y) {
  for (int oY = -2; oY <= 2; oY++) {
    for (int oX = -2; oX <= 2; oX++) {
      int newX = x + oX;
      int newY = y + oY;
      if (newX < 0 || newX >= kSectSize || newY < 0 || newY >= kSectSize)
        continue;
      m_pixels[newY * kSectSize + newX].color = sf::Color::Black;
    }
  }
}

void Shield::ShieldSection::calculatePixelCoord(int x,
                                                int y,
                                                sf::Vertex& pixel,
                                                SectorStyle style) {
  switch (style) {
    case SectorStyle::kSquare:
      m_pixels[y * kSectSize + x] = pixel;
      break;

    case SectorStyle::kSlopeUp:
      if (kSectSize - y < x) {
        m_pixels[y * kSectSize + x] = pixel;
      }
      break;

    case SectorStyle::kSlopeDown:
      if (x < y) {
        m_pixels[y * kSectSize + x] = pixel;
      }
      break;

    case SectorStyle::kSlopeUnderUp:
      if (kSectSize - x > y) {
        m_pixels[y * kSectSize + x] = pixel;
      }
      break;

    case SectorStyle::kSlopeUnderDown:
      if (x > y) {
        m_pixels[y * kSectSize + x] = pixel;
      }
      break;
  }
}
