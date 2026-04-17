cmake_minimum_required(VERSION 3.13)

# Add ELFIO library via FetchContent
include(FetchContent)
FetchContent_Declare(
    elfio
    GIT_REPOSITORY https://github.com/serge1/ELFIO.git
    GIT_TAG Release_3.12
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(elfio)

# Create the ELFParser library
add_library(ELFParser STATIC
    ELFParser.h
    ELFParser.cpp
    Fetcher.h
    Fetcher.cpp
)

target_include_directories(ELFParser
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(ELFParser
    PRIVATE
        elfio
)

target_compile_features(ELFParser PUBLIC cxx_std_17)

# Apply common compile options if available
if(COMMAND set_common_compile_options)
    set_common_compile_options(ELFParser)
endif()
