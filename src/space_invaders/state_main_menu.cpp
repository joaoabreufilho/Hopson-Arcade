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

  auto playBtn = makeButton();
  playBtn->setText("Play game");
  playBtn->setFunction([&]() { m_game_ptr->pushState<StatePlaying>(*m_game_ptr); });

  auto highscoresBtn = makeButton();
  highscoresBtn->setText("Highscores");
  highscoresBtn->setFunction(
      [&]() { m_game_ptr->pushState<StateHighscores>(*m_game_ptr); });

  auto exitBtn = makeButton();
  exitBtn->setText("Exit game");
  exitBtn->setFunction([&]() { m_game_ptr->popState(); });

  m_main_menu.addWidget(std::move(playBtn));
  m_main_menu.addWidget(std::move(highscoresBtn));
  m_main_menu.addWidget(std::move(exitBtn));
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
