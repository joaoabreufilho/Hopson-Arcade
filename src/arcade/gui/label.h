#pragma once

#include <functional>

#include "widget.h"

class Label : public Widget {
 public:
  Label();

  void setLabel(const std::string& str);

  void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
  void render(sf::RenderTarget& renderer) override;
  void setPosition(const sf::Vector2f& pos) override;
  sf::Vector2f getSize() const override;

  void disable() override;
  void enable() override;

 private:
  sf::Vector2f m_position;
  Text m_label;
};

inline std::unique_ptr<Label> makeLabel() {
  return std::make_unique<Label>();
}
