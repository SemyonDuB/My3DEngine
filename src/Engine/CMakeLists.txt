add_library(Engine "")

target_sources(Engine 
	PRIVATE Engine.cpp
	PUBLIC Engine.h)

target_include_directories(Engine 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Engine UI)

add_subdirectory(Importer)
add_subdirectory(Mesh)
add_subdirectory(NavigationSystem)
add_subdirectory(Object)
add_subdirectory(Scene)
add_subdirectory(Shader)
add_subdirectory(Viewport)
