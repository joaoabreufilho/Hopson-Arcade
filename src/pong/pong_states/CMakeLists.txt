add_library(pong_states STATIC
	state_lobby.h
	state_lobby.cpp
	state_error.h
	state_error.cpp
	pong_state_main_menu.h
	pong_state_main_menu.cpp
 )

target_link_libraries(pong_states PUBLIC
	arcade
	pong_server
)

target_include_directories(pong_states PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)
