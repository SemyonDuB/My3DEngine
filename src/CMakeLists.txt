list(APPEND CXX_FLAGS "-Wall" "-W")

file(GLOB_RECURSE resources "${CMAKE_SOURCE_DIR}/resources/*.qrc")
file(GLOB ui_files "UI/mainwindow.cpp" "UI/mainwindow.h")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOMOC_MOC_OPTIONS "-nw")

add_executable(SGE main.cpp ${resources} ${ui_files})
target_link_libraries(SGE PRIVATE Engine Qt5::Widgets)

add_subdirectory(Engine)
