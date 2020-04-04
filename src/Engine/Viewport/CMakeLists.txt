add_library(Viewport "")

target_sources(Viewport 
	PRIVATE Viewport.cpp
	PUBLIC Viewport.h)

target_include_directories(Viewport 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Viewport Qt5::Gui NavigationSystem Scene Importer Shader Engine)
