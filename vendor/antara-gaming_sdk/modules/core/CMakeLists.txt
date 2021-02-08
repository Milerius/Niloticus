add_library(antara_core_shared_sources STATIC)
target_sources(antara_core_shared_sources PRIVATE antara/gaming/core/real.path.cpp)
target_include_directories(antara_core_shared_sources PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(antara_core_shared_sources PUBLIC
        antara::default_settings
        antara::entt
        antara::refl-cpp
        PRIVATE)
if (APPLE)
    target_link_libraries(antara_core_shared_sources PRIVATE "-framework AppKit")
endif ()
add_library(antara::core ALIAS antara_core_shared_sources)

if (CMAKE_VERSION VERSION_GREATER 3.15)
    set_target_properties(antara_core_shared_sources PROPERTIES UNITY_BUILD ON)
    set_source_files_properties(antara/gaming/core/details/osx/api.scaling.mm PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
    set_property(SOURCE antara/gaming/core/details/osx/api.scaling.mm PROPERTY SKIP_UNITY_BUILD_INCLUSION ON)
    set_source_files_properties(antara/gaming/core/details/osx/api.scaling.mm PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON)
endif ()