add_library(gui STATIC 
	button.h
	button.cpp
	label.h
	label.cpp
	stack_menu.h
	stack_menu.cpp
	textbox.h
	textbox.cpp
	widget.h
	widget.cpp
)

target_link_libraries(gui PUBLIC
	util
)

target_include_directories(gui PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
