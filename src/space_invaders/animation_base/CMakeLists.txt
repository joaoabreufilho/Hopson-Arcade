add_library(animation_base STATIC
	animation_renderer.h
	animation_renderer.cpp
	starry_background.h
	starry_background.cpp
	world.h
	world.cpp
	invader_manager.h
	invader_manager.cpp
 )

target_link_libraries(animation_base PUBLIC
	arcade
	detection
	entity
)

target_include_directories(animation_base PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)
