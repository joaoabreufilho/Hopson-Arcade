add_library(pong_server STATIC
	pong_server.h
	pong_server.cpp
	net.h
 )

target_link_libraries(pong_server PUBLIC
	arcade
)

target_include_directories(pong_server PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)
