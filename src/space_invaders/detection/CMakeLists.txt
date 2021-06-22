add_library(detection STATIC
	collidable.h
	collidable.cpp
	display_info.h
 )

target_link_libraries(detection PUBLIC
)

target_include_directories(detection PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)
