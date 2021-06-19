add_library(game STATIC 
	game.h
	game.cpp
)

target_link_libraries(game PUBLIC
	util
	arcade_state
)

target_include_directories(game PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
