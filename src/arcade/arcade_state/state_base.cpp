#include "state_base.h"

#include "game.h"

StateBase::StateBase(Game& game, const char* name)
    : m_game_ptr(&game), m_name(name) {}

StateBase::StateBase(Game& game,
                     const char* name,
                     unsigned resize_window_width,
                     unsigned resize_window_height)
    : m_game_ptr(&game), m_name(name) {
  m_game_ptr->resizeWindow(resize_window_width, resize_window_height);
}
