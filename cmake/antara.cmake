if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
endif ()

include(compiler_targets)

find_package(EnTT CONFIG REQUIRED)
add_library(antara_entt INTERFACE)
target_link_libraries(antara_entt INTERFACE EnTT::EnTT)
add_library(antara::entt ALIAS antara_entt)

find_path(REFL_CPP_INCLUDE_DIRS "refl.hpp")
add_library(refl-cpp INTERFACE)
target_include_directories(refl-cpp INTERFACE ${REFL_CPP_INCLUDE_DIRS})
add_library(antara::refl-cpp ALIAS refl-cpp)

find_package(range-v3 CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
        doom_meta
        URL https://github.com/doom/meta/archive/master.zip
)

FetchContent_Declare(
        doom_st
        URL https://github.com/doom/strong_type/archive/1.0.2.tar.gz
)

set(EXPECTED_ENABLE_TESTS OFF CACHE BOOL "Override option" FORCE)
FetchContent_Declare(
        expected
        URL https://github.com/Milerius/expected/archive/patch-1.zip
)

FetchContent_Declare(adex-generics-coins
        URL https://github.com/KomodoPlatform/atomicdex-desktop-generics/archive/main.zip)

FetchContent_MakeAvailable(doom_meta doom_st expected adex-generics-coins)

set(PROJECT_COINS_VERSION "0.4.0")
configure_file(${adex-generics-coins_SOURCE_DIR}/config/${PROJECT_COINS_VERSION}-coins.json ${CMAKE_BINARY_DIR}/coins.cfg.json COPYONLY)
