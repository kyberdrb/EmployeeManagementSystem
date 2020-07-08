file(GLOB_RECURSE source_files_unit_test
    "src/*.h"
    "src/*.cpp"
)

add_executable(unit_tests ${source_files_unit_test})

target_link_libraries(
        unit_tests
        gtest
        gtest_main
        ${PROJECT_NAME}_library     # the inclusion of the 'app' project as a library into the unit test project
                                    # enables us to include the header files from the 'app' in the unit tests
)

add_test(
        unit_tests

        NAME unit
        COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
