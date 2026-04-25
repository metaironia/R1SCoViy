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

set(SOFTFLOAT_ARCH "Linux-x86_64-GCC" CACHE STRING "SoftFloat architecture directory")
set_property(CACHE SOFTFLOAT_ARCH PROPERTY STRINGS
  "Linux-x86_64-GCC" "Linux-x86_64-Clang" "ARM-VFPv2-GCC" "ARM-VFPv2-D16-GCC"
  "ARM-VFPv3-GCC" "RISC-V-GCC" "MIPS32-GCC" "MIPS64-GCC" "PPC64-GCC" "Generic-GCC"
)

FetchContent_Declare(
  softfloat
  GIT_REPOSITORY https://github.com/ucb-bar/berkeley-softfloat-3.git
  GIT_TAG        a0c6494
  GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(softfloat)
if(NOT softfloat_POPULATED)
  FetchContent_Populate(softfloat)

  if(NOT EXISTS "${softfloat_SOURCE_DIR}/build/${SOFTFLOAT_ARCH}")
    message(FATAL_ERROR "SoftFloat architecture '${SOFTFLOAT_ARCH}' not found. Check SOFTFLOAT_ARCH cache variable.")
  endif()

  file(GLOB SOFTFLOAT_SRCS CONFIGURE_DEPENDS "${softfloat_SOURCE_DIR}/source/*.c")

  add_library(softfloat STATIC ${SOFTFLOAT_SRCS})

  target_include_directories(softfloat
    PUBLIC
      ${softfloat_SOURCE_DIR}/source/include
      ${softfloat_SOURCE_DIR}/build/${SOFTFLOAT_ARCH}
  )

  set_target_properties(softfloat PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
  )
endif()

include(CommonOptions)

set(EXECUTABLE_NAME r1scoviy)

set(SIMULATOR_DIR "${CMAKE_SOURCE_DIR}/src/Simulator")
set(MATHHELPER_DIR "${CMAKE_SOURCE_DIR}/src/MathHelper")

file(GLOB_RECURSE SIMULATOR_SRC_FILES
    "${SIMULATOR_DIR}/*.cpp"
    "${MATHHELPER_DIR}/*.cpp"
)

add_executable(${EXECUTABLE_NAME} ${SIMULATOR_SRC_FILES} "${CMAKE_SOURCE_DIR}/src/main.cpp")

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

set_common_compile_options(${EXECUTABLE_NAME})

target_link_libraries_system(${EXECUTABLE_NAME} QuillLogHelper elfio softfloat)