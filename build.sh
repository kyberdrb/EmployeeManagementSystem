#!/bin/sh

clear

BUILD_OPTION=$1

SCRIPT_FULL_PATH=$(realpath "$0")
PROJECT_FULL_PATH=$(dirname "$SCRIPT_FULL_PATH")

# clean()
rm $PROJECT_FULL_PATH/vgcore.* # remove core dumps from Valgrind

BUILD_DIR_FULL_PATH="${PROJECT_FULL_PATH}/build"

rm -rf "$BUILD_DIR_FULL_PATH"
mkdir -p "$BUILD_DIR_FULL_PATH"

EXECUTABLE_NAME=$(basename "$PROJECT_FULL_PATH")

# prepareBuild()
# g++ only
#g++ -ggdb -o "${BUILD_DIR_FULL_PATH}/${EXECUTABLE_NAME}" "${PROJECT_FULL_PATH}/main.cpp" "${PROJECT_FULL_PATH}/src/SourceFile.cpp" # ... and other headers and source files

# CMake only
cmake -DPROJECT_NAME=${EXECUTABLE_NAME} -S "$PROJECT_FULL_PATH" -B "$BUILD_DIR_FULL_PATH" # 'Generate a Project Buildsystem', i.e. initialize CMake project; this generates CMakeCache.txt file which is necessary for the 'cmake --build' command, otherwise the cmake compilation will fail
                                                                                          # - also the name of the executable in this script is passed to the cmake as the name of the project which in turn produces the executable with the same name, reducing the need for manually editing the CMakeLists.txt and automatizing and generalizing the building process for any cmake project
# CMake with clang-tidy - static analysis for inspiration and safety
# cmake -DPROJECT_NAME=${EXECUTABLE_NAME} "-DCMAKE_CXX_CLANG_TIDY=/usr/bin/clang-tidy;-checks=*;-header-filter=.*" -S "$PROJECT_FULL_PATH" -B "$BUILD_DIR_FULL_PATH"

PROJECT_OPTION="app/"
if [[ "${BUILD_OPTION}" == "${PROJECT_OPTION}" ]]; then
    # buildProject()
    cmake --build "${BUILD_DIR_FULL_PATH}" --target ${EXECUTABLE_NAME} # 'Build a Project'

    # runProject()
    echo "==========================================="
    echo "             EXECUTABLE OUTPUT"
    echo "==========================================="


    EXECUTABLE_FULL_PATH="${BUILD_DIR_FULL_PATH}/bin/${EXECUTABLE_NAME}"
    "${EXECUTABLE_FULL_PATH}" # the intermediary directory 'bin' came from the CMake option 'CMAKE_RUNTIME_OUTPUT_DIRECTORY'

    # analyzeProjectsRuntime()
    echo "==========================================="
    echo "             MEMCHECK (mêmčëk)"
    echo "==========================================="

    valgrind --show-error-list=yes --leak-check=full --show-leak-kinds=all "${EXECUTABLE_FULL_PATH}"
fi

TEST_OPTION="tests/"
LIBRARY_NAME=${EXECUTABLE_NAME}_library
if [[ "${BUILD_OPTION}" == "${TEST_OPTION}" ]]; then
    # buildUnitTests()
    cmake --build "${BUILD_DIR_FULL_PATH}" --target ${LIBRARY_NAME} # 'Build a library for the Project' - not necessary to be explicitely built - just for expressiveness
    cmake --build "${BUILD_DIR_FULL_PATH}" --target unit_tests # 'Build a library for the Project'


    # prepareUnitTestsForCodeCoverage()
    "${BUILD_DIR_FULL_PATH}/bin/unit_tests" > /dev/null 2>&1

    # analyzeCodeCoverageOfUnitTests()
    echo
    echo
    echo "==========================================="
    echo "         UNIT-TESTS CODE COVERAGE"
    echo "==========================================="
    echo

    rm *.gcov

    GCOV_RESULTS_DIR_FULL_PATH="${BUILD_DIR_FULL_PATH}/gcov-unit_tests_code_coverage_results/"
    rm -rf "${GCOV_RESULTS_DIR_FULL_PATH}"

    COVERAGE_AND_PROFILING_FILES_DIR_FULL_PATH="${BUILD_DIR_FULL_PATH}"/app/CMakeFiles/${LIBRARY_NAME}.dir/src

    # SAVE THE GCOV OUTPUT TO A FILE TO REDUCE MULTIPLE COMPUTING TIMES TO ONE; then access and grep the file, not the output
    gcov "${COVERAGE_AND_PROFILING_FILES_DIR_FULL_PATH}"/* 2>/dev/null \
        | grep "${EXECUTABLE_NAME}" -A1                                     # always run after execution of unit test
                                                                            # because if coverage runs before execution of unit tests,
                                                                            # the coverage results show 0% coverage
                                                                            # for every source and header file
    mkdir -p "${GCOV_RESULTS_DIR_FULL_PATH}"
    mv *.gcov "${GCOV_RESULTS_DIR_FULL_PATH}"

    # compueAggregateCodeCoverage()
    SUM_OF_PERCENTUAL_COVERAGE=$(gcov /home/laptop/git/kyberdrb/EmployeeManagementSystem/build/app/CMakeFiles/EmployeeManagementSystem_library.dir/src/* 2>/dev/null | grep "EmployeeManagementSystem" -A1 | grep "Lines executed" | cut -d':' -f2 | cut -d'%' -f1 | awk '{ sum += $1; } END { print sum; }')
    NUMBER_OF_SOURCE_FILES=$(gcov /home/laptop/git/kyberdrb/EmployeeManagementSystem/build/app/CMakeFiles/EmployeeManagementSystem_library.dir/src/* 2>/dev/null | grep "EmployeeManagementSystem" -A1 | grep "Lines executed" | wc -l)
    AVERAGE_CODE_COVERAGE=$(echo "${SUM_OF_PERCENTUAL_COVERAGE} ${NUMBER_OF_SOURCE_FILES}" | awk '{printf "%.3f\n", $1/$2}')

    echo
    echo "Average code coverage: ${AVERAGE_CODE_COVERAGE} %"

    # analyzeUnitTestsRuntime()
    echo
    echo
    echo "==========================================="
    echo "        UNIT-TESTS OUTPUT + MEMCHECK"
    echo "==========================================="
    echo

    rm -rf "${GCOV_RESULTS_DIR_FULL_PATH}"      # DUPLICATE

    valgrind --show-error-list=yes --leak-check=full --show-leak-kinds=all "${BUILD_DIR_FULL_PATH}/bin/unit_tests"

    mkdir -p "${GCOV_RESULTS_DIR_FULL_PATH}"    # DUPLICATE
    mv *.gcov "${GCOV_RESULTS_DIR_FULL_PATH}"   # DUPLICATE
fi
