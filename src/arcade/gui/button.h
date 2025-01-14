/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file button.h
 * @brief Single button representation.
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
    @brief Enum for the size of a button
*/
enum class ButtonSize {
  kSmall,
  kWide,
};

/**
 * @class Button
 * @brief A class that represents a single button
 *
 */
class Button : public Widget {
 public:
  /**
   * @brief Construct a new Button object
   *
   * @param s The size of the button
   */
  Button(ButtonSize s = ButtonSize::kWide);

  /**
   * @brief Sets a function callback for when the button is pressed
   *
   * @param function The callback function
   */
  void setFunction(std::function<void(void)> function);

  /**
   * @brief Set the text that appears on the button
   *
   * @param text The text on the button
   */

  void setText(const std::string& text);

  /**
   * @brief Set the texture to appear on the background of the button
   *
   * @param texture
   */
  void setTexture(const sf::Texture& texture);

  /**
   * @brief Handles window events
   * Certain events like clicks and mouseovers can trigger the button
   * to do something, this function handles such events
   * @param e The SFML event that contains event information
   * @param window The window that game is being played on
   */
  void handleEvent(sf::Event e, const sf::RenderWindow& window) override;

  /**
   * @brief Render the button
   * Renders the button to a render target
   * @param renderer The target to render the button to
   */
  void render(sf::RenderTarget& renderer) override;

  /**
   * @brief Set the position of the button
   *
   * @param pos The position to set the button to
   */
  void setPosition(const sf::Vector2f& pos) override;

  /**
   * @brief Get the buttons size
   * Retruns the size of the button as it appears on the window
   * @return sf::Vector2f The size of the button
   */
  sf::Vector2f getSize() const override;

  void disable() override;
  void enable() override;

 private:
  /**
   * @brief Realigns the position of the text to be centered in the
   * window
   *
   */
  void updateText();

  sf::Vector2f m_position;
  Rectangle m_button;
  Text m_text;
  std::function<void(void)> m_function = []() {};
  bool m_is_disabled = false;
};

/**
 * @brief Creates a button object
 *
 * @return std::unique_ptr<Button> A unique pointer to a new button
 * object
 */
inline std::unique_ptr<Button> makeButton() {
  return std::make_unique<Button>();
}
/** @} */