set(LIB_NAME QuillLogHelper)

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