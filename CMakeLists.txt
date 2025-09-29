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
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

# ---------------------------
# Biblioteca com a lógica principal
# ---------------------------
add_library(logica_pessoa STATIC src/pessoa.cpp)
target_include_directories(logica_pessoa PUBLIC src) # PUBLIC para que os targets que linkam herdem o include
target_link_libraries(logica_pessoa PUBLIC nlohmann_json::nlohmann_json) # Linka json aqui se a lib precisar

# ---------------------------
# Executável principal
# ---------------------------
add_executable(leitor src/main.cpp)
target_link_libraries(leitor PRIVATE logica_pessoa)

# Comando para copiar o teste.json para o diretório de saída do executável após a compilação
add_custom_command(TARGET leitor POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/data/teste.json
    $<TARGET_FILE_DIR:leitor>
)

# ---------------------------
# Testes unitários
# ---------------------------
add_executable(tests tests/test_pessoa.cpp)
target_link_libraries(tests PRIVATE gtest gtest_main logica_pessoa)

# Detecta e adiciona testes automaticamente
include(GoogleTest)
gtest_discover_tests(tests)