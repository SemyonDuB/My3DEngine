cmake_minimum_required(VERSION 3.1)

project(SGE LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(OpenGL)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

include_directories(include/)

#set(BUILD_ASSIMP_TOOLS  ON)
#set(ASSIMP_BUILD_STATIC_LIB ON)
#add_subdirectory(libs/assimp-4.0.1)

file(GLOB_RECURSE header "include/*.h" "include/*/*.h")
file(GLOB_RECURSE src "src/*.cpp" "src/*/*.cpp")
file(GLOB_RECURSE resources "resources/*/*.qrc")

add_executable(SGE ${src} ${header} ${resources} "ui/mainwindow.ui")
qt5_use_modules(SGE Core Gui Widgets OpenGL)
target_link_libraries(SGE ${QT_LIBRARIES} ${OPENGL_LIBRARIES} assimp)


