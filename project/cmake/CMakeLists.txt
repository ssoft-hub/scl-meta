# Header-only library: meta (depends on utility)
# Produces targets:
#   - scl-meta (real interface target)
#   - SCL::meta (ALIAS in build tree)
# Exported/imported name is set to "meta" so installed import is SCL::meta.

# Resolve module root directory (module/meta)
get_filename_component(SCL_META_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

set(MODULE meta)
add_library(scl-${MODULE} INTERFACE)
add_library(SCL::${MODULE} ALIAS scl-${MODULE})

# Ensure the imported/install name is SCL::meta
set_target_properties(scl-${MODULE} PROPERTIES EXPORT_NAME meta)

target_include_directories(scl-${MODULE}
    INTERFACE
        $<BUILD_INTERFACE:${SCL_META_ROOT}/include>
        $<INSTALL_INTERFACE:include>
)

# Universal dependency on SCL::utility:
# - In superbuilds, SCL::utility target is already defined.
# - In standalone builds, locate installed package SCL with 'utility' component.
if (NOT TARGET SCL::utility)
    find_package(SCL CONFIG REQUIRED COMPONENTS utility)
endif()

target_link_libraries(scl-${MODULE}
    INTERFACE
        SCL::utility
)
