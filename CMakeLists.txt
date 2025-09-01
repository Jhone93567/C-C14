cmake_minimum_required(VERSION 3.16)
project(Aula_12_08 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

include(FetchContent)

# ---------------------------
# nlohmann_json via FetchContent
# ---------------------------
FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

# ---------------------------
# GoogleTest via FetchContent
# ---------------------------
# Configura o GTest para não instalar e não construir o GoogleMock
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# ---------------------------
# Executável principal
# ---------------------------
add_executable(leitor src/main.cpp src/pessoa.cpp)
target_include_directories(leitor PRIVATE src)
target_link_libraries(leitor PRIVATE nlohmann_json::nlohmann_json)

# ---------------------------
# Testes unitários
# ---------------------------
add_executable(tests tests/test_pessoa.cpp src/pessoa.cpp)
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE gtest gtest_main nlohmann_json::nlohmann_json)

# Detecta e adiciona testes automaticamente
include(GoogleTest)
gtest_discover_tests(tests)
