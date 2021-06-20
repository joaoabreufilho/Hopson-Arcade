/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file stack_menu.h
 * @brief Stack menu handler
 *
 * - \subpage Subsystem: Arcade GUI
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_gui */
/** @{ */
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "non_copyable.h"
#include "widget.h"

/**
 * @class StackMenu
 * @brief Class for a stack menu
 * A stack menu is a menu where its widgets appear in a vertical stack
 */
class StackMenu : public NonCopyable {
 public:
  StackMenu(const sf::RenderWindow& window, float base_y, int width = 300);
  StackMenu(const sf::Vector2f& position, int width);

  StackMenu(StackMenu&& other);
  StackMenu& operator=(StackMenu&& other);

  ~StackMenu() = default;

  Widget* addWidget(std::unique_ptr<Widget> w);
  /*
  template<typename T, typename... Args>
  void addWidget(Args&&... args) {
      auto w = std::make_unique<T>(std::forward<Args>(args)...);
      initWidget(*w);
      m_widgets.push_back(std::move(w));
  }*/

  void setTitle(const std::string& title);

  void handleEvent(sf::Event e, const sf::RenderWindow& window);
  void render(sf::RenderTarget& renderer);

 private:
  void initWidget(Widget& w);

  std::vector<std::unique_ptr<Widget>> m_widgets;
  sf::RectangleShape m_background;

  sf::Vector2f m_base_position;
  sf::Vector2f m_base_size;

  Widget::Text m_title_text;
};
/** @} */