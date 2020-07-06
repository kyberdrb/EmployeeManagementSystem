file(GLOB_RECURSE source_files
    "src/*.h"
    "src/*.cpp"

    "client/*.h"
    "client/*.cpp"
)

add_executable(${PROJECT_NAME} ${source_files})

file(GLOB_RECURSE source_files_library
    "src/*.h"
    "src/*.cpp"
)

add_library(${PROJECT_NAME}_library ${source_files_library})

target_include_directories(
        ${PROJECT_NAME}_library

        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
