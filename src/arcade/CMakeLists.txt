add_subdirectory(arcade_state)
add_subdirectory(gui)
add_subdirectory(input)
add_subdirectory(resources)
add_subdirectory(util)
add_subdirectory(game)

add_library(arcade INTERFACE)

target_link_libraries(arcade INTERFACE
    arcade_state
    gui
    input
    resources
    util
    game
)

target_include_directories(arcade INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/arcade_state
	${CMAKE_CURRENT_SOURCE_DIR}/gui
	${CMAKE_CURRENT_SOURCE_DIR}/resources
	${CMAKE_CURRENT_SOURCE_DIR}/util
    ${CMAKE_CURRENT_SOURCE_DIR}/game

)