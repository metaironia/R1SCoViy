cmake_minimum_required(VERSION 3.13)

project(R1SCOVIY LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory(${CMAKE_SOURCE_DIR}/src/LogHelper)

target_include_directories(QuillLogHelper SYSTEM INTERFACE
    ${quill_SOURCE_DIR}/include
)

include(FetchContent)
FetchContent_Declare(
    elfio
    GIT_REPOSITORY https://github.com/serge1/ELFIO.git
    GIT_TAG Release_3.12
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(elfio)

include(CommonOptions)

set(EXECUTABLE_NAME r1scoviy)

set(SIMULATOR_DIR "${CMAKE_SOURCE_DIR}/src/Simulator")

file(GLOB_RECURSE SIMULATOR_SRC_FILES
    "${SIMULATOR_DIR}/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SIMULATOR_SRC_FILES} "${CMAKE_SOURCE_DIR}/src/main.cpp")

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

set_common_compile_options(${EXECUTABLE_NAME})

message(STATUS "elfio_SOURCE_DIR: ${elfio_SOURCE_DIR}")

target_link_libraries_system(${EXECUTABLE_NAME} QuillLogHelper elfio)