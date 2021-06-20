#include "state_base.h"

#include "game.h"

StateBase::StateBase(Game& game, const char* name)
    : m_game_ptr(&game), m_name(name) {}

StateBase::StateBase(Game& game,
                     const char* name,
                     unsigned resizeWindowWidth,
                     unsigned resizeWindowHeight)
    : m_game_ptr(&game), m_name(name) {
  m_game_ptr->resizeWindow(resizeWindowWidth, resizeWindowHeight);
}
