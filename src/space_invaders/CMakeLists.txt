add_library(space_invaders
    animation_renderer.cpp
    animation_renderer.h
    collidable.cpp
    collidable.h
    display_info.h
    explosion.cpp
    explosion.h
    invader_manager.cpp
    invader_manager.h
    invader.cpp
    invader.h
    player.cpp
    player.h
    projectile.cpp
    projectile.h
    shield.cpp
    shield.h
    starry_background.cpp
    starry_background.h
    state_highscores.cpp
    state_highscores.h
    state_main_menu.cpp
    state_main_menu.h
    state_playing.cpp
    state_playing.h
    ufo.cpp
    ufo.h
    world.cpp
    world.h
)

target_link_libraries(space_invaders PUBLIC
	arcade
)

target_include_directories(space_invaders PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)