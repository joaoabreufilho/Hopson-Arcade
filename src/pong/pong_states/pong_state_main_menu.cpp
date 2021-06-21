#include "pong_state_main_menu.h"

#include "button.h"
#include "game.h"
#include "state_lobby.h"
#include "textbox.h"

constexpr unsigned kWidth = 800;
constexpr unsigned kHeight = 600;

PongStateMainMenu::PongStateMainMenu(Game& game)
    : StateBase(game, "Main Menu", kWidth, kHeight),
      m_main_menu(game.getWindow(), kHeight / 2 - 100),
      m_join_menu(game.getWindow(), kHeight / 2 - 100),
      m_create_lobby_menu(game.getWindow(), kHeight / 2 - 100),
      m_active_menu_ptr(&m_main_menu) {
  m_banner.setSize({(float)kWidth, 200});
  m_banner.setTexture(&ResourceHolder::get().m_textures.get("pong/logo"));

  {
    auto vsComputer = makeButton();
    vsComputer->setText("Play Vs Computer");
    // vsComputer->setFunction(
    //    [&]() { m_game_ptr->pushState<StateLobby>(*m_game_ptr); });

    auto playBtn = makeButton();
    playBtn->setText("Create Lobby");
    playBtn->setFunction([&]() { m_active_menu_ptr = &m_create_lobby_menu; });

    auto joinBtn = makeButton();
    joinBtn->setText("Join Lobby");
    joinBtn->setFunction([&]() { m_active_menu_ptr = &m_join_menu; });

    auto exitBtn = makeButton();
    exitBtn->setText("Exit game");
    exitBtn->setFunction([&]() { m_game_ptr->popState(); });

    m_main_menu.addWidget(std::move(vsComputer));
    m_main_menu.addWidget(std::move(playBtn));
    m_main_menu.addWidget(std::move(joinBtn));
    m_main_menu.addWidget(std::move(exitBtn));
    m_main_menu.setTitle("Choose Action");
  }
  {
    auto nameBox = makeTextBox(m_name);
    nameBox->setLabel("Enter your name");

    auto joinBtn = makeButton();
    joinBtn->setText("Start Lobby");
    joinBtn->setFunction([&]() {
      if (m_name.empty()) {
        m_name = "Host";
      }
      m_game_ptr->pushState<StateLobby>(*m_game_ptr, m_name);
    });

    auto backBtn = makeButton();
    backBtn->setText("Back");
    backBtn->setFunction([&]() { m_active_menu_ptr = &m_main_menu; });

    m_create_lobby_menu.setTitle("Create Lobby");
    m_create_lobby_menu.addWidget(std::move(nameBox));
    m_create_lobby_menu.addWidget(std::move(joinBtn));
    m_create_lobby_menu.addWidget(std::move(backBtn));
  }
  {
    auto ipBox = makeTextBox(m_join_ip);
    ipBox->setLabel("Enter host IP Address");

    auto nameBox = makeTextBox(m_name);
    nameBox->setLabel("Enter your name");

    auto joinBtn = makeButton();
    joinBtn->setText("Join Lobby");
    joinBtn->setFunction([&]() {
      if (m_name.empty()) {
        m_name = "Guest";
      }
      m_game_ptr->pushState<StateLobby>(*m_game_ptr, m_join_ip, m_name);
    });

    auto backBtn = makeButton();
    backBtn->setText("Back");
    backBtn->setFunction([&]() { m_active_menu_ptr = &m_main_menu; });

    m_join_menu.setTitle("");
    m_join_menu.addWidget(std::move(nameBox));
    m_join_menu.addWidget(std::move(ipBox));
    m_join_menu.addWidget(std::move(joinBtn));
    m_join_menu.addWidget(std::move(backBtn));
  }
}

void PongStateMainMenu::handleEvent(sf::Event e) {
  m_active_menu_ptr->handleEvent(e, m_game_ptr->getWindow());
}

void PongStateMainMenu::update(sf::Time deltaTime) {
  (void)deltaTime;
}

void PongStateMainMenu::render(sf::RenderTarget& renderer) {
  m_active_menu_ptr->render(renderer);
  renderer.draw(m_banner);
}