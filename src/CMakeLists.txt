set(hopson-arcade "${PROJECT_NAME}")

#set(SFML_STATIC_LIBRARIES TRUE)

add_subdirectory(arcade)
add_subdirectory(pong)
add_subdirectory(space_invaders)


add_executable(${PROJECT_NAME} "") 

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        arcade
        pong
        space_invaders
        pthread
        sfml-audio
        sfml-network
        sfml-graphics
        sfml-window
        sfml-system
        pthread
)