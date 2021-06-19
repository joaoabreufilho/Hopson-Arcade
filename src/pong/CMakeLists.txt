add_subdirectory(pong_states)
add_subdirectory(pong_server)

add_library(pong STATIC 
	pong_player.h
)

target_link_libraries(pong PUBLIC
	pong_states
	pong_server
)

target_include_directories(pong PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
