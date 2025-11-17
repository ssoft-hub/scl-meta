# Build one executable per subdirectory under module/meta/example/*

get_filename_component(SCL_META_EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../example" ABSOLUTE)

if (EXISTS "${SCL_META_EXAMPLE_DIR}")
    file(GLOB SCL_META_EXAMPLE_SUBDIRS LIST_DIRECTORIES true "${SCL_META_EXAMPLE_DIR}/*")

    foreach(subdir IN LISTS SCL_META_EXAMPLE_SUBDIRS)
        if (IS_DIRECTORY "${subdir}")
            get_filename_component(name "${subdir}" NAME)
            file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
                "${subdir}/*.c" "${subdir}/*.cc" "${subdir}/*.cpp"
            )

            if (srcs)
                set(tgt "meta_example_${name}")
                add_executable(${tgt} ${srcs})
                target_link_libraries(${tgt} PRIVATE SCL::meta)
                target_compile_features(${tgt} PRIVATE cxx_std_20)
            endif()
        endif()
    endforeach()
endif()
