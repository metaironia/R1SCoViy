function(set_common_compile_options target_name)
    
    target_compile_options(${target_name} PRIVATE
        -Wshadow -Winit-self -Wcast-align -Wundef -Wfloat-equal -Winline -Wredundant-decls
        -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default
        -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy
        -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers
        -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing
        -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
    )

    target_compile_features(${target_name} PRIVATE cxx_std_17)

    target_compile_options(${target_name} PRIVATE
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Release>:-O3 -DNDEBUG>
    )

    target_compile_definitions(${target_name} PRIVATE
        $<$<CONFIG:Debug>:-DQUILL_COMPILE_ACTIVE_LOG_LEVEL=QUILL_COMPILE_ACTIVE_LOG_LEVEL_DEBUG>
        $<$<CONFIG:Release>:-DQUILL_COMPILE_ACTIVE_LOG_LEVEL=QUILL_COMPILE_ACTIVE_LOG_LEVEL_INFO>
    )
endfunction()

function(target_link_libraries_system target)
  set(libs ${ARGN})
  foreach(lib ${libs})
    get_target_property(lib_include_dirs ${lib} INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(${target} SYSTEM PRIVATE ${lib_include_dirs})
    target_link_libraries(${target} ${lib})
  endforeach(lib)
endfunction(target_link_libraries_system)