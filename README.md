# Leitura de JSON em C++ com nlohmann/json

Este projeto demonstra como ler e interpretar arquivos **JSON** em C++ usando a biblioteca **[nlohmann/json](https://github.com/nlohmann/json)**, uma biblioteca *header-only*.  
O programa lê um arquivo `teste.json` e exibe os campos `nome` e `idade` no terminal.

---

## Dependências

- **Compilador C++** (com suporte a C++17 ou superior).
- **CMake** (>= 3.10).

---

## Configuração do Build com CMake

O projeto já inclui um `CMakeLists.txt` mínimo para configuração:

---

## Como compilar e executar

#### 1. Crie a pasta build
~~~
mkdir build
cd build
~~~
#### 2. Gere os arquivos de build
~~~
cmake ..
~~~
#### 3. Compile o código
~~~
cmake --build .
~~~
#### 4. Execute o código
~~~
./Leitor
~~~

**Atenção: O código abre o arquivo teste.json que deve estar um nível acima da pasta `build/`**