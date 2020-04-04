find_package(Boost 1.72 REQUIRED)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test Boost::Boost)

enable_testing()

add_test(NAME boost_test COMMAND $<TARGET_FILE:cpp_test>)
