#include "game.h"

#include <iostream>

Game::Game() : m_window({1, 1}, "Hopson Arcade") {
  m_window.setPosition({m_window.getPosition().x, 0});
  m_window.setFramerateLimit(60);

  sf::Image icon;
  icon.loadFromFile("res/txrs/icon.png");
  m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Runs the main loop
void Game::run() {
  constexpr unsigned TPS = 30;  // ticks per seconds
  const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
  unsigned ticks = 0;

  sf::Clock timer;
  auto lastTime = sf::Time::Zero;
  auto lag = sf::Time::Zero;

  // Main loop of the game
  while (m_window.isOpen() && !m_states.empty()) {
    auto& state = getCurrentState();

    // Get times
    auto time = timer.getElapsedTime();
    auto elapsed = time - lastTime;
    lastTime = time;
    lag += elapsed;

    // Real time update
    state.handleInput();
    state.update(elapsed);
    counter.update();

    // Fixed time update
    while (lag >= timePerUpdate) {
      ticks++;
      lag -= timePerUpdate;
      state.fixedUpdate(elapsed);
    }

    // Render
    m_window.clear();
    state.render(m_window);
    counter.draw(m_window);
    m_window.display();

    // Handle window events
    handleEvent();
    updateStates();
  }
}

// Tries to pop the current game state
void Game::updateStates() {
  switch (m_action.type) {
    case Action::Type::kPush:
      m_states.push_back(std::move(m_action.state));
      m_action.type = Action::Type::kNone;
      break;

    case Action::Type::kPop:
      m_states.pop_back();
      if (!m_states.empty()) {
        getCurrentState().onOpen();
      }
      m_action.type = Action::Type::kNone;
      break;

    case Action::Type::kChange:
      m_states.pop_back();
      m_states.push_back(std::move(m_action.state));
      m_action.type = Action::Type::kNone;
      break;

    case Action::Type::kQuit:
      m_states.clear();
      break;

    default:
      break;
  }
}

// Handles window events, called every frame
void Game::handleEvent() {
  sf::Event e;

  while (m_window.pollEvent(e)) {
    getCurrentState().handleEvent(e);
    switch (e.type) {
      case sf::Event::Closed:
        m_window.close();
        break;

      default:
        break;
    }
  }
}

// Returns a reference to the current game state
StateBase& Game::getCurrentState() {
  return *m_states.back();
}

void Game::pushState(std::unique_ptr<StateBase> state) {
  m_states.push_back(std::move(state));
  getCurrentState().onOpen();
}

// Flags a boolean for the game to pop state
void Game::popState() {
  m_action.type = Action::Type::kPop;
}

void Game::exitGame() {
  m_action.type = Action::Type::kQuit;
}

// on tin
const sf::RenderWindow& Game::getWindow() const {
  return m_window;
}

void Game::resizeWindow(unsigned width, unsigned height) {
  m_window.close();
  m_window.create({width, height}, "Hopson Arcade");
  m_window.setFramerateLimit(60);
}
