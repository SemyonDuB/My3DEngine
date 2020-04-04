add_library(UI "")

target_sources(UI 
	PRIVATE MainWindow.cpp
	PUBLIC MainWindow.h)

target_include_directories(UI
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(UI Viewport Qt5::Widgets)
