add_library(Scene "")

target_sources(Scene 
	PRIVATE BaseScene.cpp
			Scene.cpp
	PUBLIC BaseScene.h
		   Scene.h)

target_include_directories(Scene 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Scene Shader Object Qt5::Core OpenGL::OpenGL)
