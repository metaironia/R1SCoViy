cmake_minimum_required(VERSION 3.13)

project(R1SCOVIY LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(FetchContent)
FetchContent_Declare(
    quill
    GIT_REPOSITORY https://github.com/odygrd/quill.git
    GIT_TAG v11.1.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(quill)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/LogHelper)

include(CommonOptions)

set(EXECUTABLE_NAME r1scoviy)

set(SIMULATOR_DIR "${CMAKE_SOURCE_DIR}/src/Simulator")

file(GLOB_RECURSE SIMULATOR_SRC_FILES
    "${SIMULATOR_DIR}/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SIMULATOR_SRC_FILES} "${CMAKE_SOURCE_DIR}/src/main.cpp")

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}"
)

set_common_compile_options(${EXECUTABLE_NAME})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE QuillLogHelper quill::quill)

target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)