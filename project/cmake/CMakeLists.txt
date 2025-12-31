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

# ---- Make headers visible in IDE ----
set(SCL_META_PUBLIC_DIR "${SCL_META_ROOT}/include")
file(GLOB_RECURSE SCL_META_HEADERS CONFIGURE_DEPENDS
    "${SCL_META_PUBLIC_DIR}/*.h"
    "${SCL_META_PUBLIC_DIR}/*.hpp"
    "${SCL_META_PUBLIC_DIR}/*.hh"
    "${SCL_META_PUBLIC_DIR}/*.hxx"
    "${SCL_META_PUBLIC_DIR}/*.inl"
)

# ---- Private headers and sources (implementation files) ----
set(SCL_META_PRIVATE_DIR "${SCL_META_ROOT}/src")
file(GLOB_RECURSE SCL_META_PRIVATE_HEADERS CONFIGURE_DEPENDS
    "${SCL_META_PRIVATE_DIR}/*.h"
    "${SCL_META_PRIVATE_DIR}/*.hpp"
    "${SCL_META_PRIVATE_DIR}/*.hh"
    "${SCL_META_PRIVATE_DIR}/*.hxx"
    "${SCL_META_PRIVATE_DIR}/*.inl"
)
file(GLOB_RECURSE SCL_META_PRIVATE_SOURCES CONFIGURE_DEPENDS
    "${SCL_META_PRIVATE_DIR}/*.c"
    "${SCL_META_PRIVATE_DIR}/*.cpp"
)

# ---- Add implementation sources to the target normally ----
target_sources(scl-${MODULE} PRIVATE
    ${SCL_META_PRIVATE_SOURCES}
)

# Prefer CMake 3.23+ FILE_SET HEADERS so IDEs (VS, Xcode) attach headers to the target itself
# IMPORTANT:
# - The HEADERS file set must always keep a single scope across the entire project.
# - We use PUBLIC for the HEADERS file set in this target.
# - Do NOT add private headers to the HEADERS file set; that causes scope conflicts.
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.23")
    target_sources(scl-${MODULE} PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${SCL_META_PUBLIC_DIR}
            FILES ${SCL_META_HEADERS}
    )
endif()

# --- IDE-only aggregation target (Qt Creator, etc., will show these files) ---
add_custom_target(scl_meta ALL
    SOURCES
        ${SCL_META_HEADERS}
        ${SCL_META_PRIVATE_HEADERS}
        ${SCL_META_PRIVATE_SOURCES}
)

# ---- Group files nicely in IDEs (Visual Studio/Xcode) ----
if (SCL_META_HEADERS)
    source_group(TREE "${SCL_META_PUBLIC_DIR}"  FILES ${SCL_META_HEADERS})
    source_group(TREE "${SCL_META_PRIVATE_DIR}" FILES ${SCL_META_PRIVATE_HEADERS} ${SCL_META_PRIVATE_SOURCES})
endif()
