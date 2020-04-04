add_library(Importer "")

target_sources(Importer 
	PRIVATE Import.cpp
	PUBLIC Import.h)

target_include_directories(Importer 
	PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Importer Scene Object Mesh Qt5::Gui assimp::assimp)
