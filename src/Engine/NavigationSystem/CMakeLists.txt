add_library(NavigationSystem "")

target_sources(NavigationSystem 
	PRIVATE Navigation.cpp
	PUBLIC Navigation.h)

target_include_directories(NavigationSystem 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(NavigationSystem Qt5::Gui Scene)
