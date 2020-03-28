add_library(Scene "")

target_sources(Scene 
	PRIVATE BaseScene.cpp
			scene.cpp
	PUBLIC BaseScene.h
		   scene.h)

target_include_directories(Scene 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Scene PRIVATE Qt5::Core Qt5::Gui OpenGL::OpenGL Engine)
