add_library(Shader "")

target_sources(Shader 
	PRIVATE Shader.cpp
	PUBLIC Shader.h)

target_include_directories(Shader 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Shader Qt5::Gui)
