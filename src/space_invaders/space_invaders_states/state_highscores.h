/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file state_highscores.h
 * @brief High Scores state manager.
 *
 * - \subpage Subsystem: Space Invaders States
 *
 * \date Jun 2021
 */
/** @addtogroup space_invaders_states */
/** @{ */
#pragma once

#include <stack_menu.h>
#include <state_base.h>
#include <widget.h>

#include "starry_background.h"

/**
 * @class StateHighscores
 * @brief High Score State Manager.
 */
class StateHighscores : public StateBase {
  using Entry = std::pair<std::string, int>;

  struct EntryBox {
   public:
    EntryBox(int position, const std::string& name, int score);

    void draw(sf::RenderTarget& renderer);

   private:
    sf::RectangleShape m_background;
    Widget::Text m_name_text;
    Widget::Text m_score_text;
  };

  enum class State { Submitting, Viewing };

 public:
  StateHighscores(Game& game, int score);
  StateHighscores(Game& game);

  void handleEvent(sf::Event e) override;
  void handleInput() override{};
  void update(sf::Time deltaTime) override;
  void render(sf::RenderTarget& renderer) override;

  static int getHighestScore();

 private:
  void initViewMenu();
  void initSubmitMenu();

  void switchToViewMenu();
  void createHighscoreView();
  void loadScores();
  void writeScores();
  void sortScores();
  void submitScore();

  StackMenu m_submit_score_menu;
  StackMenu m_highscore_menu;
  StackMenu* m_active_menu_ptr;

  std::vector<Entry> m_scores;
  std::vector<EntryBox> m_entry_boxes;

  StarryBackground m_background;

  State m_state;

  std::string m_submit_string;
  int m_score_to_submit = 0;

  sf::RectangleShape m_banner;
};
/** @} */