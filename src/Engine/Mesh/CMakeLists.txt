add_library(Mesh "")

target_sources(Mesh 
	PRIVATE Mesh.cpp
	PUBLIC Mesh.h)

target_include_directories(Mesh 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Mesh Qt5::Gui)

