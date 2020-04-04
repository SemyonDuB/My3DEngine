add_library(Object "")

target_sources(Object 
	PRIVATE Object.cpp
	PUBLIC Object.h)

target_include_directories(Object 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Object Qt5::Gui Mesh)
