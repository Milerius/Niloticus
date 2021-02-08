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

##worker shared deps
add_library(${PROJECT_NAME}_worker_shared_deps STATIC)
target_link_libraries(${PROJECT_NAME}_worker_shared_deps PUBLIC antara::world)
target_sources(${PROJECT_NAME}_worker_shared_deps PRIVATE
        ## application
        src/niloticus/application/worker.app.cpp

        ## services
        src/niloticus/services/markets/coingecko/coingecko.service.cpp)
target_include_directories(${PROJECT_NAME}_worker_shared_deps PUBLIC src)
add_library(${PROJECT_NAME}::worker_shared_deps ALIAS ${PROJECT_NAME}_worker_shared_deps)

##server shared deps
add_library(${PROJECT_NAME}_server_shared_deps INTERFACE)
target_link_libraries(${PROJECT_NAME}_server_shared_deps INTERFACE restinio::restinio)
add_library(${PROJECT_NAME}::server_shared_deps ALIAS ${PROJECT_NAME}_server_shared_deps)

add_library(${PROJECT_NAME}_shared_deps STATIC)
target_link_libraries(${PROJECT_NAME}_shared_deps
        PRIVATE
        spdlog::spdlog
        nlohmann_json::nlohmann_json
        date::date
        date::date-tz)
target_include_directories(${PROJECT_NAME}_shared_deps PUBLIC src)
target_sources(${PROJECT_NAME}_shared_deps PRIVATE
        ##base
        src/niloticus/base/base.cpp

        ##config
        src/niloticus/config/config.json.cpp

        ##logging
        src/niloticus/log/logging.cpp
        )
add_library(${PROJECT_NAME}::shared_deps ALIAS ${PROJECT_NAME}_shared_deps)

##! Worker executable
add_executable(${PROJECT_NAME}_worker)
target_sources(${PROJECT_NAME}_worker PRIVATE
        ## main
        cmd/worker/main.cpp)
target_link_libraries(${PROJECT_NAME}_worker PRIVATE ${PROJECT_NAME}::shared_deps ${PROJECT_NAME}::worker_shared_deps)

##! Server executable
add_executable(${PROJECT_NAME}_server)
target_sources(${PROJECT_NAME}_server PRIVATE
        ##application
        src/niloticus/application/server.application.cpp

        ## main
        cmd/server/main.cpp
        )
target_link_libraries(${PROJECT_NAME}_server PRIVATE ${PROJECT_NAME}::shared_deps ${PROJECT_NAME}::server_shared_deps)


##! Tests
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
        ${PROJECT_NAME}::server_shared_deps
        ${PROJECT_NAME}::worker_shared_deps
        doctest::doctest)
