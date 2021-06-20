#include "pong_state_main_menu.h"

#include "button.h"
#include "game.h"
#include "state_lobby.h"
#include "textbox.h"

constexpr unsigned WIDTH = 800;
constexpr unsigned HEIGHT = 600;

PongStateMainMenu::PongStateMainMenu(Game& game)
    : StateBase(game, "Main Menu", WIDTH, HEIGHT),
      m_mainMenu(game.getWindow(), HEIGHT / 2 - 100),
      m_joinMenu(game.getWindow(), HEIGHT / 2 - 100),
      m_createLobbyMenu(game.getWindow(), HEIGHT / 2 - 100),
      mp_activeMenu(&m_mainMenu) {
  m_banner.setSize({(float)WIDTH, 200});
  m_banner.setTexture(&ResourceHolder::get().m_textures.get("pong/logo"));

  {
    auto vsComputer = makeButton();
    vsComputer->setText("Play Vs Computer");
    // vsComputer->setFunction(
    //    [&]() { m_game_ptr->pushState<StateLobby>(*m_game_ptr); });

    auto playBtn = makeButton();
    playBtn->setText("Create Lobby");
    playBtn->setFunction([&]() { mp_activeMenu = &m_createLobbyMenu; });

    auto joinBtn = makeButton();
    joinBtn->setText("Join Lobby");
    joinBtn->setFunction([&]() { mp_activeMenu = &m_joinMenu; });

    auto exitBtn = makeButton();
    exitBtn->setText("Exit game");
    exitBtn->setFunction([&]() { m_game_ptr->popState(); });

    m_mainMenu.addWidget(std::move(vsComputer));
    m_mainMenu.addWidget(std::move(playBtn));
    m_mainMenu.addWidget(std::move(joinBtn));
    m_mainMenu.addWidget(std::move(exitBtn));
    m_mainMenu.setTitle("Choose Action");
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
    backBtn->setFunction([&]() { mp_activeMenu = &m_mainMenu; });

    m_createLobbyMenu.setTitle("Create Lobby");
    m_createLobbyMenu.addWidget(std::move(nameBox));
    m_createLobbyMenu.addWidget(std::move(joinBtn));
    m_createLobbyMenu.addWidget(std::move(backBtn));
  }
  {
    auto ipBox = makeTextBox(m_joinIp);
    ipBox->setLabel("Enter host IP Address");

    auto nameBox = makeTextBox(m_name);
    nameBox->setLabel("Enter your name");

    auto joinBtn = makeButton();
    joinBtn->setText("Join Lobby");
    joinBtn->setFunction([&]() {
      if (m_name.empty()) {
        m_name = "Guest";
      }
      m_game_ptr->pushState<StateLobby>(*m_game_ptr, m_joinIp, m_name);
    });

    auto backBtn = makeButton();
    backBtn->setText("Back");
    backBtn->setFunction([&]() { mp_activeMenu = &m_mainMenu; });

    m_joinMenu.setTitle("");
    m_joinMenu.addWidget(std::move(nameBox));
    m_joinMenu.addWidget(std::move(ipBox));
    m_joinMenu.addWidget(std::move(joinBtn));
    m_joinMenu.addWidget(std::move(backBtn));
  }
}

void PongStateMainMenu::handleEvent(sf::Event e) {
  mp_activeMenu->handleEvent(e, m_game_ptr->getWindow());
}

void PongStateMainMenu::update(sf::Time deltaTime) {
  (void)deltaTime;
}

void PongStateMainMenu::render(sf::RenderTarget& renderer) {
  mp_activeMenu->render(renderer);
  renderer.draw(m_banner);
}