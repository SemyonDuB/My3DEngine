add_executable(Importer_test ImporterTest.cpp)
target_link_libraries(Importer_test Boost::Boost assimp::assimp)

file(COPY cube.obj DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_test(NAME Importer_test COMMAND $<TARGET_FILE:Importer_test>)
