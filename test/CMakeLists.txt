project(Testing)

file(GLOB_RECURSE SOURCES TestScanner.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(run_crux_test ${SOURCES}
        TestAst.cpp
        TestParser.cpp)

add_custom_target(
    update_submodules
    COMMAND ${CMAKE_COMMAND} -E echo "Updating submodules"
    COMMAND git submodule update --init --recursive --remote
)

add_dependencies(run_crux_test update_submodules)

target_link_libraries(run_crux_test ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(run_crux_test gtest gtest_main)