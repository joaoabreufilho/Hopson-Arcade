/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file widget.h
 * @brief widget handler
 *
 * - \subpage Subsystem: Arcade GUI
 *
 * \date Jun 2021
 */
/** @addtogroup arcade */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "resource_holder.h"

/**
 * @class Widget
 * @brief widget handler.
 */
class Widget {
 public:
  virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

  virtual void render(sf::RenderTarget& renderer) = 0;

  virtual void setPosition(const sf::Vector2f& pos) = 0;

  virtual sf::Vector2f getSize() const = 0;

  virtual void disable() = 0;
  virtual void enable() = 0;

  class Text : public sf::Text {
   public:
    Text();
  };

  class Rectangle : public sf::RectangleShape {
   public:
    bool isRolledOn(const sf::RenderWindow& window) const;
    bool isClicked(sf::Event, const sf::RenderWindow& window);
  };
};
/** @} */