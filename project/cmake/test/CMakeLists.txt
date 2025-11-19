# Generate tests for meta: one test target per subdirectory under module/meta/test/*
# Supports GTest, doctest, and Catch2 depending on availability/toggles.

include(${CMAKE_SOURCE_DIR}/project/cmake/SCLDependencies.cmake)

get_filename_component(SCL_META_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/../../test" ABSOLUTE)

if (EXISTS "${SCL_META_TEST_DIR}")
    file(GLOB SCL_META_TEST_SUBDIRS LIST_DIRECTORIES true "${SCL_META_TEST_DIR}/*")

    foreach(subdir IN LISTS SCL_META_TEST_SUBDIRS)
        if (IS_DIRECTORY "${subdir}")
            get_filename_component(name "${subdir}" NAME)
            file(GLOB_RECURSE srcs CONFIGURE_DEPENDS
                "${subdir}/*.c" "${subdir}/*.cc" "${subdir}/*.cpp"
            )
            if (NOT srcs)
                continue()
            endif()

            # --- GoogleTest ---
            if (GTEST_FOUND)
                set(tgt "meta_${name}_gtest")
                add_executable(${tgt} ${srcs})
                target_link_libraries(${tgt} PRIVATE SCL::meta GTest::gtest_main)
                target_compile_features(${tgt} PRIVATE cxx_std_20)
                include(GoogleTest)
                gtest_discover_tests(${tgt} DISCOVERY_TIMEOUT 30)
            endif()

            # --- doctest ---
            if (DOCTEST_FOUND)
                set(tgt "meta_${name}_doctest")
                add_executable(${tgt} ${srcs})
                target_link_libraries(${tgt} PRIVATE SCL::meta doctest::doctest)
                target_compile_features(${tgt} PRIVATE cxx_std_20)
                add_test(NAME ${tgt} COMMAND ${tgt})
            endif()

            # --- Catch2 ---
            if (CATCH2_FOUND)
                if (TARGET Catch2::Catch2WithMain)
                    set(tgt "meta_${name}_catch2")
                    add_executable(${tgt} ${srcs})
                    target_link_libraries(${tgt} PRIVATE SCL::meta Catch2::Catch2WithMain)
                    target_compile_features(${tgt} PRIVATE cxx_std_20)
                    include(Catch)
                    catch_discover_tests(${tgt})
                elseif (TARGET Catch2::Catch2)
                    # For Catch2 v2, tests must supply their own main()
                    set(tgt "meta_${name}_catch2_v2")
                    add_executable(${tgt} ${srcs})
                    target_link_libraries(${tgt} PRIVATE SCL::meta Catch2::Catch2)
                    target_compile_features(${tgt} PRIVATE cxx_std_20)
                    add_test(NAME ${tgt} COMMAND ${tgt})
                endif()
            endif()
        endif()
    endforeach()
endif()
