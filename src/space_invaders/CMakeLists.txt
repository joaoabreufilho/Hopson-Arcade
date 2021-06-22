add_subdirectory(entity)
add_subdirectory(detection)
add_subdirectory(animation_base)
add_subdirectory(space_invaders_states)

add_library(space_invaders
    state_main_menu.cpp
    state_main_menu.h
)

target_link_libraries(space_invaders PUBLIC
	arcade
    entity
    detection
    animation_base
    space_invaders_states
)

target_include_directories(space_invaders PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}

)