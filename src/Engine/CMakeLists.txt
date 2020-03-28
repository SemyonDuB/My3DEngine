add_library(Engine "")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

target_sources(Engine 
	PRIVATE engine.cpp
			import.cpp
			mesh.cpp
			object.cpp
			shader.cpp
			viewport.cpp

	PUBLIC engine.h
		   import.h
		   mesh.h
		   object.h
		   shader.h
		   viewport.h)


target_include_directories(Engine 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Engine PRIVATE NavigationSystem Scene
	Qt5::OpenGL Qt5::Core Qt5::Gui Qt5::Widgets assimp)

add_subdirectory(NavigationSystem)
add_subdirectory(Scene)
