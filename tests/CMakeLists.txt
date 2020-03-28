add_executable(cpp_test test.cpp)

target_link_libraries(cpp_test PRIVATE Boost::unit_test_framework)
target_compile_definitions(cpp_test PRIVATE BOOST_TEST_DYN_LINK)

enable_testing()

add_test(NAME boost_test COMMAND $<TARGET_FILE:cpp_test>)
