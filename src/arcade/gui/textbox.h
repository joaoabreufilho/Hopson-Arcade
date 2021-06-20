/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file textbox.h
 * @brief Class definition for a textbox
 *
 * - \subpage Subsystem: Arcade GUI
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_gui */
/** @{ */
#pragma once

#include <functional>

#include "widget.h"

/**
 * @class TextBox
 * @brief Textbox handler.
 */
class TextBox : public Widget {
 public:
  TextBox(std::string& mod_string);

  void setLabel(const std::string& str);
  void setTexture(const sf::Texture& tex);

  void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
  void render(sf::RenderTarget& renderer) override;
  void setPosition(const sf::Vector2f& pos) override;
  sf::Vector2f getSize() const override;

  void disable() override;
  void enable() override;

 private:
  void handleClick(sf::Event e, const sf::RenderWindow& window);
  void handleTextInput(sf::Event e);

  bool isValidCharacter(unsigned char key_code);
  bool isBackspace(unsigned char key_code);

  sf::Vector2f m_position;

  Rectangle m_rect;
  Text m_text;
  Text m_label;
  std::string* m_mod_string_ptr;

  bool m_is_active = false;
  bool m_is_disabled = false;
};

inline std::unique_ptr<TextBox> makeTextBox(std::string& mod_str) {
  return std::make_unique<TextBox>(mod_str);
}
/** @} */