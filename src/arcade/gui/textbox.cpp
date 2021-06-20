#include "textbox.h"

#include <iostream>

TextBox::TextBox(std::string& mod_string) : m_mod_string_ptr(&mod_string) {
  m_text.setString(mod_string);
  m_label.setCharacterSize(15);
  m_rect.setFillColor({52, 152, 219});
  m_rect.setSize({256, 64});
}

void TextBox::setLabel(const std::string& str) {
  m_label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window) {
  handleClick(e, window);
  handleTextInput(e);
}

void TextBox::render(sf::RenderTarget& renderer) {
  if (!m_is_active) {
    m_rect.setFillColor({52, 152, 219});
  } else {
    m_rect.setFillColor({82, 132, 239});
  }
  renderer.draw(m_rect);
  renderer.draw(m_label);
  renderer.draw(m_text);
}

void TextBox::setPosition(const sf::Vector2f& pos) {
  m_position = pos;

  m_rect.setPosition(m_position);
  m_label.setPosition(m_position.x, m_position.y +
                                        m_label.getGlobalBounds().height -
                                        m_rect.getGlobalBounds().height / 2);
  m_text.setPosition(m_position);
  m_text.move(5, m_rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const {
  return {m_rect.getSize().x,
          m_rect.getSize().y + m_label.getGlobalBounds().height};
}

void TextBox::handleClick(sf::Event e, const sf::RenderWindow& window) {
  if (!m_is_disabled) {
    auto pos = sf::Mouse::getPosition(window);
    if (m_rect.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
      if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
          m_is_active = true;
        }
      }
    } else {
      if (e.type == sf::Event::MouseButtonPressed) {
        if (e.mouseButton.button == sf::Mouse::Left) {
          m_is_active = false;
        }
      }
    }
  }
}

void TextBox::handleTextInput(sf::Event e) {
  if (!m_is_disabled) {
    switch (e.type) {
      case sf::Event::TextEntered:
        if (m_is_active) {
          // Get the key that was entered
          unsigned char key_code = e.text.unicode;

          if (isValidCharacter(key_code)) {
            if (m_text.getGlobalBounds().width + 30 <=
                m_rect.getGlobalBounds().width) {
              m_mod_string_ptr->push_back(key_code);
            }
          } else if (isBackspace(key_code)) {
            // prevents popping back an empty string
            if (m_mod_string_ptr->length() > 0)
              m_mod_string_ptr->pop_back();
          }
          m_text.setString(*m_mod_string_ptr);
        }
        break;

      default:
        break;
    }
  }
}

bool TextBox::isValidCharacter(unsigned char key_code) {
  return ((key_code >= 48) && (key_code <= 57)) ||   // Numbers
         ((key_code >= 65) && (key_code <= 90)) ||   // Uppercase
         ((key_code >= 97) && (key_code <= 122)) ||  // Lowercase
         key_code == 32 ||                          // Space
         key_code == 46;                            // dot
}

bool TextBox::isBackspace(unsigned char keycode) {
  return keycode == 8;
}

void TextBox::disable() {
  m_text.setFillColor({100, 100, 100});
  m_rect.setFillColor({50, 50, 50});
  m_is_disabled = true;
}

void TextBox::enable() {
  m_text.setFillColor(sf::Color::White);
  m_rect.setFillColor(sf::Color::Black);
  m_is_disabled = false;
}
