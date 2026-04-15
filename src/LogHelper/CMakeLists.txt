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

target_include_directories(${LIB_NAME} SYSTEM PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_features(${LIB_NAME} PRIVATE cxx_std_17)

target_compile_options(${LIB_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

target_compile_definitions(${LIB_NAME} PRIVATE
    $<$<CONFIG:Debug>:QUILL_LOG_LEVEL=QUILL_LOG_LEVEL_TRACE>
    $<$<CONFIG:Release>:QUILL_LOG_LEVEL=QUILL_LOG_LEVEL_INFO>
)

target_link_libraries(${LIB_NAME} PUBLIC quill::quill)