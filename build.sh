#!/bin/sh

clear

BUILD_OPTION=$1

SCRIPT_FULL_PATH=$(realpath "$0")
PROJECT_FULL_PATH=$(dirname "$SCRIPT_FULL_PATH")

# clean()
# remove core dumps from Valgrind
rm $PROJECT_FULL_PATH/vgcore.*

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

PROJECT_OPTION="project"
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

TEST_OPTION="test"
if [[ "${BUILD_OPTION}" == "${TEST_OPTION}" ]]; then
    # buildUnitTests()
    cmake --build "${BUILD_DIR_FULL_PATH}" --target ${EXECUTABLE_NAME}_library # 'Build a library for the Project' - not necessary to be explicitely built - just for expressiveness
    cmake --build "${BUILD_DIR_FULL_PATH}" --target unit_tests # 'Build a library for the Project'

    # analyzeUnitTestsRuntime()
    echo "==========================================="
    echo "        UNIT-TESTS OUTPUT + MEMCHECK"
    echo "==========================================="

    valgrind --show-error-list=yes --leak-check=full --show-leak-kinds=all "./build/bin/unit_tests"
fi
