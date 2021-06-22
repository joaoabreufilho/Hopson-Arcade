/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file shield.h
 * @brief Shield entity handler.
 *
 * - \subpage Subsystem: Space Invaders Entity
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_entity */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "collidable.h"

class Projectile;

/**
 * @class Shield
 * @brief Shield entity handler.
 */
class Shield : private Collidable {
  constexpr static int kSectSize = 20;

  enum class SectorStyle {
    kSquare,
    kSlopeUp,
    kSlopeDown,
    kSlopeUnderUp,
    kSlopeUnderDown
  };
  class ShieldSection : public Collidable {
   public:
    ShieldSection(float tl_x, float tl_y, SectorStyle style);

    void draw(sf::RenderTarget& target);

    const sf::Vector2f& getPosition() const;
    void onCollide([[maybe_unused]] Collidable& other) {}

    sf::Vector2f isTouching(const Projectile& other);

    void destroyArea(int x, int y);

   private:
    void calculatePixelCoord(int x, int y, sf::Vertex& v, SectorStyle style);
    std::array<sf::Vertex, kSectSize * kSectSize> m_pixels;
    sf::Vector2f m_position;
  };

 public:
  constexpr static int kSize = kSectSize * 4;

  Shield(float x);

  void draw(sf::RenderTarget& target);
  bool isTouching(const Projectile& projectile);

  const sf::Vector2f& getPosition() const;
  void onCollide([[maybe_unused]] Collidable& other) {}

 private:
  ShieldSection& getSection(int x, int y);

  void destroyPoint(float relX, float relY);

  std::vector<ShieldSection> m_sections;
  sf::Vector2f m_position;
};
/** @} */