find_package(Boost 1.72 REQUIRED)
find_package(assimp REQUIRED)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test Boost::Boost)
add_test(NAME cpp_test COMMAND $<TARGET_FILE:cpp_test>)

add_subdirectory(EngineTest)
