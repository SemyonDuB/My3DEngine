file(GLOB_RECURSE resources "resources/*.qrc")

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(OpenGL REQUIRED OpenGL)
find_package(assimp REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-nw")

add_executable(SGE main.cpp ${resources})
target_link_libraries(SGE Qt5::Widgets UI)

add_subdirectory(UI)
add_subdirectory(Engine)
