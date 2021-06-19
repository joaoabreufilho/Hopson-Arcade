add_library(input STATIC 
	keyboard.h
	keyboard.cpp
)

target_link_libraries(input PUBLIC
)

target_include_directories(input PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}	
)
