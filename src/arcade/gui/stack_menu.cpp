#include "stack_menu.h"

#include "resource_holder.h"

constexpr float kBaseY = 95.0f;

StackMenu::StackMenu(const sf::RenderWindow& window, float baseY, int width)
    : m_base_position((float)window.getSize().x / 2.0f, baseY),
      m_base_size(width, 20) {
  m_background.setOutlineThickness(2);
  m_background.setOutlineColor(sf::Color::Green);
  m_background.setFillColor({100, 100, 100, 230});
  m_background.setSize(m_base_size);
  m_background.setPosition(m_base_position.x - m_base_size.x / 2, baseY - 30);

  m_title_text.setPosition(0, baseY - 35);
  m_title_text.setOutlineColor(sf::Color::Black);
  m_title_text.setOutlineThickness(1);
  m_title_text.setCharacterSize(30);
}

StackMenu::StackMenu(const sf::Vector2f& position, int width)
    : m_base_position(position), m_base_size(width, 20) {
  m_background.setOutlineThickness(2);
  m_background.setOutlineColor(sf::Color::Green);
  m_background.setFillColor({100, 100, 100, 230});
  m_background.setSize(m_base_size);
  m_background.setPosition(m_base_position.x - m_base_size.x / 2,
                           position.y - 30);

  m_title_text.setPosition(position.x, position.y - 35);
  m_title_text.setOutlineColor(sf::Color::Black);
  m_title_text.setOutlineThickness(1);
  m_title_text.setCharacterSize(30);
}

StackMenu::StackMenu(StackMenu&& other)
    : m_widgets(std::move(other.m_widgets)),
      m_background(std::move(other.m_background)),
      m_base_position(other.m_base_position),
      m_base_size(other.m_base_size) {}

StackMenu& StackMenu::operator=(StackMenu&& other) {
  m_widgets = std::move(other.m_widgets);
  m_background = std::move(other.m_background);
  m_base_position = other.m_base_position;
  m_base_size = other.m_base_size;

  return *this;
}

Widget* StackMenu::addWidget(std::unique_ptr<Widget> w) {
  initWidget(*w);
  m_widgets.push_back(std::move(w));
  return m_widgets.back().get();
}

void StackMenu::initWidget(Widget& widget) {
  widget.setPosition(
      {m_base_position.x - widget.getSize().x / 2, m_base_position.y});

  m_base_position.y += widget.getSize().y + 25;
  m_base_size.y += widget.getSize().y + 25;
  m_background.setSize(m_base_size);
}

void StackMenu::setTitle(const std::string& title) {
  m_title_text.setString(title);
  m_title_text.setPosition(m_background.getPosition().x +
                              m_background.getSize().x / 2 -
                              m_title_text.getGlobalBounds().width / 2,
                          m_title_text.getPosition().y);
  m_base_position.y += m_title_text.getGlobalBounds().height;
  m_base_size.y += m_title_text.getGlobalBounds().height;
  m_background.setSize(m_base_size);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window) {
  for (auto& widget : m_widgets) {
    widget->handleEvent(e, window);
  }
}

void StackMenu::render(sf::RenderTarget& renderer) {
  renderer.draw(m_background);
  renderer.draw(m_title_text);
  for (auto& widget : m_widgets) {
    widget->render(renderer);
  }
}
