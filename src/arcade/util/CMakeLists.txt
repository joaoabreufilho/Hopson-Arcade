add_library(util STATIC 
	animation.h
	animation.cpp
	file_util.h
	file_util.cpp
	fps_counter.h
	fps_counter.cpp
	maths.h
	non_copyable.h
	non_moveable.h
	random.h
	toggle_key.h
	toggle_key.cpp
)

target_link_libraries(util PUBLIC
	resources
)

target_include_directories(util PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}	
)
