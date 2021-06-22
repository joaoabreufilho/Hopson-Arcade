add_library(space_invaders_states STATIC
	state_highscores.cpp
	state_highscores.h
	state_playing.cpp
	state_playing.h
 )

target_link_libraries(space_invaders_states PUBLIC
	arcade
	entity
	detection
	animation_base
)

target_include_directories(space_invaders_states PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)
