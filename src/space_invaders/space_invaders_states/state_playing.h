/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file state_playing.h
 * @brief Playing state manager.
 *
 * - \subpage Subsystem: Space Invaders States
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_states */
/** @{ */
#pragma once

#include "stack_menu.h"
#include "state_base.h"
#include "world.h"

/**
 * @class StatePlaying
 * @brief The main state; where all the gameplay happens.
 */
class StatePlaying : public StateBase {
 public:
  StatePlaying(Game& game);

  void handleEvent(sf::Event e) override;
  void handleInput() override;
  void update(sf::Time delta_time) override;
  void render(sf::RenderTarget& renderer) override;

 private:
  World m_world;

  int m_score = 0;
  bool m_is_gameover;
  sf::Clock m_game_over_clock;

  StackMenu m_game_over_menu;

  /**
   * @class LifeDisplay
   * @brief Displays how many lives the player has left.
   */
  class LifeDisplay {
   public:
    LifeDisplay();

    void draw(sf::RenderTarget& window, int lives);

   private:
    Widget::Text m_label;
    sf::RectangleShape m_life_stamp;
  } m_life_display;

  /**
   * @class ScoreDisplay
   * @brief Displays the Player's current score
   */
  class ScoreDisplay {
   public:
    ScoreDisplay(float centreX, const std::string& text);

    void update(int newScore);

    void draw(sf::RenderTarget& target);

    int getCurrentScoreDisplayed() const;

   private:
    void updateDisplay();

    Widget::Text m_label;
    std::string m_text;
    int m_current_score;
    float m_center_position;
  } m_score_display, m_highest_score_display;
};
/** @} */