#include "state_playing.h"

#include "button.h"
#include "game.h"
#include "resource_holder.h"
#include "state_highscores.h"

StatePlaying::StatePlaying(Game& game)
    : StateBase(game, "Playing the game"),
      m_game_over_menu(game.getWindow(), kInvadersHeight / 3),
      m_score_display(kInvaderWidth / 8, "Score"),
      m_highest_score_display(kInvaderWidth / 2, "HighScore") {
  auto button_mm_ptr = std::make_unique<Button>();
  button_mm_ptr->setText("Main Menu\n");
  button_mm_ptr->setFunction([&]() { m_game_ptr->popState(); });

  auto btn_submit_ptr = std::make_unique<Button>();
  btn_submit_ptr->setText("Submit Score");
  btn_submit_ptr->setFunction(
      [&]() { m_game_ptr->changeState<StateHighscores>(*m_game_ptr, m_score); });

  auto button_exit_ptr = std::make_unique<Button>();
  button_exit_ptr->setText("Exit game\n");
  button_exit_ptr->setFunction([&]() { m_game_ptr->exitGame(); });

  m_game_over_menu.setTitle("GAME  OVER");
  m_game_over_menu.addWidget(std::move(button_mm_ptr));
  m_game_over_menu.addWidget(std::move(btn_submit_ptr));
  m_game_over_menu.addWidget(std::move(button_exit_ptr));

  m_highest_score_display.update(StateHighscores::getHighestScore());
}

void StatePlaying::handleEvent(sf::Event e) {
  if (m_is_gameover) {
    m_game_over_menu.handleEvent(e, m_game_ptr->getWindow());
  }
}

void StatePlaying::handleInput() {
  m_world.input();
}

void StatePlaying::update(sf::Time delta_time) {
  if (!m_is_gameover) {
    m_score += m_world.update(delta_time.asSeconds());
    m_score_display.update(m_score);

    if (m_score > m_highest_score_display.getCurrentScoreDisplayed()) {
      m_highest_score_display.update(m_score);
    }
  }

  m_is_gameover = m_world.isGameOver();
}

void StatePlaying::render(sf::RenderTarget& renderer) {
  m_world.draw(renderer);

  m_life_display.draw(renderer, m_world.getPlayer().getLives());
  m_score_display.draw(renderer);
  m_highest_score_display.draw(renderer);

  if (m_is_gameover) {
    m_game_over_menu.render(renderer);
  }
}

///////////////////////////////////////////////
//     display member functions       ///
StatePlaying::LifeDisplay::LifeDisplay() {
  m_life_stamp.setSize({Player::kWidth / 2, Player::kWidth / 2});
  m_life_stamp.setTexture(&ResourceHolder::get().m_textures.get("si/player"));
  m_life_stamp.setTextureRect({0, 0, 11, 8});
  m_label.setPosition(kInvaderWidth - (Player::kWidth * 5), 10);
  m_label.setString("LIVES");
  m_label.setOutlineThickness(0);
}

void StatePlaying::LifeDisplay::draw(sf::RenderTarget& window, int lives) {
  float xOrigin =
      m_label.getPosition().x + m_label.getGlobalBounds().width + 10;
  float yOrigin =
      m_label.getPosition().y + m_label.getGlobalBounds().height / 2;

  window.draw(m_label);
  for (int i = 0; i < lives; i++) {
    m_life_stamp.setPosition(xOrigin + i * Player::kWidth / 2 + i * 10, yOrigin);
    window.draw(m_life_stamp);
  }
}

StatePlaying::ScoreDisplay::ScoreDisplay(float x, const std::string& text)
    : m_text(text), m_center_position(x) {
  updateDisplay();
  m_label.setOutlineThickness(0);
}

void StatePlaying::ScoreDisplay::update(int newScore) {
  m_current_score = newScore;
  updateDisplay();
}

void StatePlaying::ScoreDisplay::draw(sf::RenderTarget& target) {
  target.draw(m_label);
}

int StatePlaying::ScoreDisplay::getCurrentScoreDisplayed() const {
  return m_current_score;
}

void StatePlaying::ScoreDisplay::updateDisplay() {
  m_label.setString(m_text + "   " + std::to_string(m_current_score));
  m_label.setPosition(m_center_position - m_label.getGlobalBounds().width / 2,
                      15);
}
