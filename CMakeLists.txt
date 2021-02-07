cmake_minimum_required(VERSION 3.18)
project(niloticus)

set(CMAKE_CXX_STANDARD 20)

## Deps
find_package(restinio CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-http-parser CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


add_library(${PROJECT_NAME}_shared_deps STATIC)
target_link_libraries(${PROJECT_NAME}_shared_deps PRIVATE restinio::restinio spdlog::spdlog nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME}_shared_deps PUBLIC src)
target_sources(${PROJECT_NAME}_shared_deps PRIVATE
        ##config
        src/niloticus/config/config.json.cpp)
add_library(${PROJECT_NAME}::shared_deps ALIAS ${PROJECT_NAME}_shared_deps)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}::shared_deps)

add_executable(${PROJECT_NAME}_tests)
target_sources(${PROJECT_NAME}_tests PRIVATE tests/main.tests.cpp
        ## config
        tests/config/config.tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        ${PROJECT_NAME}::shared_deps
        doctest::doctest)
