set(LIB_NAME QuillLogHelper)

include(FetchContent)
FetchContent_Declare(
    quill
    GIT_REPOSITORY https://github.com/odygrd/quill.git
    GIT_TAG v11.1.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(quill)

include(CommonOptions)

add_library(${LIB_NAME} STATIC
        OverwriteMacros.h
        QuillLogHelper.h
        QuillLogHelper.cpp
)

target_include_directories(${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_common_compile_options(${LIB_NAME})

target_link_libraries(${LIB_NAME} PUBLIC quill::quill)