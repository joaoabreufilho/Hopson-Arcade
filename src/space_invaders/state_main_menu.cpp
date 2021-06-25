#include "state_main_menu.h"

#include <game.h>
#include <button.h>

#include "state_highscores.h"
#include "state_playing.h"

StateMainMenu::StateMainMenu(Game& game)
    : StateBase(game, "Main Menu", kInvaderWidth, kInvadersHeight),
      m_main_menu(game.getWindow(), kInvadersHeight / 2 - 100) {
  m_banner.setSize({(float)kInvaderWidth, 200});
  m_banner.setTexture(&ResourceHolder::get().m_textures.get("si/logo"));

  auto play_btn_ptr = makeButton();
  play_btn_ptr->setText("Play game");
  play_btn_ptr->setFunction([&]() { m_game_ptr->pushState<StatePlaying>(*m_game_ptr); });

  auto high_scores_btn_ptr = makeButton();
  high_scores_btn_ptr->setText("Highscores");
  high_scores_btn_ptr->setFunction(
      [&]() { m_game_ptr->pushState<StateHighscores>(*m_game_ptr); });

  auto exit_btn_ptr = makeButton();
  exit_btn_ptr->setText("Exit game");
  exit_btn_ptr->setFunction([&]() { m_game_ptr->popState(); });

  m_main_menu.addWidget(std::move(play_btn_ptr));
  m_main_menu.addWidget(std::move(high_scores_btn_ptr));
  m_main_menu.addWidget(std::move(exit_btn_ptr));
  m_main_menu.setTitle("Choose Action");
}

void StateMainMenu::handleEvent(sf::Event e) {
  m_main_menu.handleEvent(e, m_game_ptr->getWindow());
}

void StateMainMenu::update(sf::Time deltaTime) {
  m_background.update(deltaTime.asSeconds());
}

void StateMainMenu::render(sf::RenderTarget& renderer) {
  m_background.draw(renderer);
  m_main_menu.render(renderer);
  renderer.draw(m_banner);
}
