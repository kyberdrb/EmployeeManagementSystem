file(GLOB_RECURSE source_files_unit_test
    "src/*.h"
    "src/*.cpp"
)

add_executable(unit_tests ${source_files_unit_test})

target_link_libraries(
        unit_tests
        gtest_main
        ${PROJECT_NAME}_library
)

add_test(
        unit_tests

        NAME unit
        COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
