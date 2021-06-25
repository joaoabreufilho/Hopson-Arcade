#include "state_highscores.h"

#include <button.h>
#include <game.h>
#include <textbox.h>
#include "display_info.h"

#include <fstream>
#include <iostream>
#include <sstream>

const auto kScoresPath = "res/space_invaders/scores.txt";

StateHighscores::StateHighscores(Game& game, int score)
    : StateHighscores(game) {
  initSubmitMenu();
  m_score_to_submit = score;
  m_active_menu_ptr = &m_submit_score_menu;
  m_state = State::Submitting;
}

StateHighscores::StateHighscores(Game& game)
    : StateBase(game, "Highscores"),
      m_submit_score_menu(game.getWindow(), 100.0f),
      m_highscore_menu(game.getWindow(), kInvadersHeight - 100.0f),
      m_state(State::Viewing) {
  initViewMenu();
  m_active_menu_ptr = &m_highscore_menu;
  m_banner.setSize({(float)kInvaderWidth, 200});
  m_banner.setTexture(
      &ResourceHolder::get().m_textures.get("si/highscores"));
  createHighscoreView();
}

void StateHighscores::handleEvent(sf::Event e) {
  m_active_menu_ptr->handleEvent(e, m_game_ptr->getWindow());
}

void StateHighscores::update(sf::Time deltaTime) {
  m_background.update(deltaTime.asSeconds());
}

void StateHighscores::render(sf::RenderTarget& renderer) {
  m_background.draw(renderer);
  m_active_menu_ptr->render(renderer);
  if (m_state == State::Viewing) {
    for (auto& entry : m_entry_boxes) {
      entry.draw(renderer);
    }
    renderer.draw(m_banner);
  }
}

int StateHighscores::getHighestScore() {
  std::ifstream in_file(kScoresPath);
  std::string buffer;

  std::getline(in_file, buffer, ',');
  std::getline(in_file, buffer, ',');
  if (buffer.empty())
    return 0;
  else
    return std::stoi(buffer);
}

void StateHighscores::initViewMenu() {
  loadScores();

  auto back_btn_ptr = makeButton();
  back_btn_ptr->setText("Main Menu");
  back_btn_ptr->setFunction([&]() { m_game_ptr->popState(); });
  m_highscore_menu.addWidget(std::move(back_btn_ptr));
}

void StateHighscores::initSubmitMenu() {
  auto name_text_box_ptr = makeTextBox(m_submit_string);
  name_text_box_ptr->setLabel("Click text box to enter name");

  auto submit_btn_ptr = makeButton();
  submit_btn_ptr->setText("Submit Score");
  submit_btn_ptr->setFunction([&]() {
    if (!m_submit_string.empty()) {
      submitScore();
      switchToViewMenu();
    }
  });

  auto back_btn_ptr = makeButton();
  back_btn_ptr->setText("View HighScores");
  back_btn_ptr->setFunction([&]() {
    loadScores();
    switchToViewMenu();
  });

  m_submit_score_menu.addWidget(std::move(name_text_box_ptr));
  m_submit_score_menu.addWidget(std::move(submit_btn_ptr));
  m_submit_score_menu.addWidget(std::move(back_btn_ptr));
}

void StateHighscores::switchToViewMenu() {
  m_state = State::Viewing;
  m_active_menu_ptr = &m_highscore_menu;
  createHighscoreView();
}

void StateHighscores::createHighscoreView() {
  loadScores();
  sortScores();
  m_entry_boxes.clear();
  for (unsigned i = 0; i < m_scores.size(); i++) {
    auto& name = m_scores[i].first;
    auto score = m_scores[i].second;

    m_entry_boxes.emplace_back(i + 1, name, score);
    if (i >= 9)
      return;  // Only show top 10 scores
  }
}

void StateHighscores::loadScores() {
  m_scores.clear();
  std::ifstream in_file(kScoresPath);
  std::string line;
  int switcher = 0;
  std::string name;
  int score;
  while (std::getline(in_file, line, ',')) {
    if (switcher++ % 2 == 0) {
      name = line;
    } else {
      score = std::stoi(line);
      m_scores.emplace_back(std::make_pair(name, score));
    }
  }
  sortScores();
}

void StateHighscores::writeScores() {
  sortScores();
  std::ofstream out_file(kScoresPath);
  for (auto& entry : m_scores) {
    out_file << entry.first << "," << entry.second << ",";
  }
}

void StateHighscores::sortScores() {
  std::sort(m_scores.begin(), m_scores.end(),
            [](Entry& a, Entry& b) { return a.second > b.second; });
}

void StateHighscores::submitScore() {
  loadScores();
  m_scores.emplace_back(std::make_pair(m_submit_string, m_score_to_submit));
  writeScores();
}

StateHighscores::EntryBox::EntryBox(int position,
                                    const std::string& name,
                                    int score) {
  float size = 35;
  float y = 200 + position * (size - 2);
  m_background.setSize({kInvaderWidth / 1.5f, size});
  m_background.setPosition(
      {kInvaderWidth / 2 - m_background.getGlobalBounds().width / 2, y});

  m_name_text.setCharacterSize((unsigned)size - 5);
  m_score_text.setCharacterSize((unsigned)size - 5);

  m_name_text.setString(std::to_string(position) + "     " + name);
  m_score_text.setString(std::to_string(score));

  m_name_text.setPosition(m_background.getPosition());
  m_score_text.setPosition(m_background.getPosition().x +
                              m_background.getGlobalBounds().width -
                              m_score_text.getGlobalBounds().width - 10,
                          y);

  m_background.setOutlineThickness(2);
  m_background.setOutlineColor(sf::Color::Green);
  m_background.setFillColor(position % 2 == 0 ? sf::Color::Black
                                              : sf::Color{50, 40, 50});
}

void StateHighscores::EntryBox::draw(sf::RenderTarget& renderer) {
  renderer.draw(m_background);
  renderer.draw(m_name_text);
  renderer.draw(m_score_text);
}
