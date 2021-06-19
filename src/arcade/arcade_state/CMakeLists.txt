add_library(arcade_state STATIC 
	state_base.h
	state_base.cpp
)

target_link_libraries(arcade_state PUBLIC
	util
	game
)

target_include_directories(arcade_state PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
