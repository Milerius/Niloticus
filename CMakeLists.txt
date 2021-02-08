cmake_minimum_required(VERSION 3.18)
project(niloticus)

set(CMAKE_CXX_STANDARD 17)

## Deps
find_package(restinio CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-http-parser CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(antara)
add_subdirectory(vendor/antara-gaming_sdk/modules)


add_library(${PROJECT_NAME}_shared_deps STATIC)
target_link_libraries(${PROJECT_NAME}_shared_deps PUBLIC restinio::restinio antara::world PRIVATE
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        date::date
        date::date-tz)
target_include_directories(${PROJECT_NAME}_shared_deps PUBLIC src)
target_sources(${PROJECT_NAME}_shared_deps PRIVATE
        ##application
        src/niloticus/application/app.cpp
        ##base
        src/niloticus/base/base.cpp

        ##config
        src/niloticus/config/config.json.cpp

        ##logging
        src/niloticus/log/logging.cpp

        ##services
        src/niloticus/services/markets/coingecko/coingecko.service.cpp
        )
add_library(${PROJECT_NAME}::shared_deps ALIAS ${PROJECT_NAME}_shared_deps)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}::shared_deps)

add_executable(${PROJECT_NAME}_tests)
target_sources(${PROJECT_NAME}_tests PRIVATE tests/main.tests.cpp
        ##base
        tests/base/base.tests.cpp
        ## config
        tests/config/config.tests.cpp
        ##logging
        tests/logging/logging.tests.cpp
        ##! services
        tests/services/markets/coingecko.services.tests.cpp
        )
target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        ${PROJECT_NAME}::shared_deps
        doctest::doctest)
