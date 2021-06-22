add_library(entity STATIC
	explosion.h
	explosion.cpp
	invader.h
	invader.cpp
	player.h
	player.cpp
	projectile.h
	projectile.cpp	
	shield.h
	shield.cpp
	ufo.h
	ufo.cpp

 )

target_link_libraries(entity PUBLIC
	arcade
	detection
)

target_include_directories(entity PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)
