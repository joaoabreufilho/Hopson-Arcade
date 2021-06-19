add_library(resources STATIC 
	resource_holder.h
	resource_holder.cpp
	resource_manager.h

)

target_link_libraries(resources PUBLIC
	util
)

target_include_directories(resources PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
