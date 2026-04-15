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

target_link_libraries(${EXECUTABLE_NAME} PRIVATE QuillLogHelper quill::quill)