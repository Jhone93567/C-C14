cmake_minimum_required(VERSION 3.14.0)
project(Aula-12-08 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)

FetchContent_MakeAvailable(json)

add_executable(Leitor src/main.cpp)

target_link_libraries(Leitor PRIVATE nlohmann_json::nlohmann_json)
