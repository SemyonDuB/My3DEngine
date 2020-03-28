add_library(NavigationSystem "")

target_sources(NavigationSystem 
	PRIVATE navigation.cpp
	PUBLIC navigation.h)

target_include_directories(NavigationSystem 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(NavigationSystem PRIVATE Qt5::Gui Scene Engine)
