#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{
    std::ifstream arquivo("../teste.json");

    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        return 1;
    }

    json dados;

    arquivo >> dados;

    std::string nome = dados["NOME"];

    int idade = dados["IDADE"];

    std::cout << "Nome: " << nome << std::endl;
    std::cout << "Idade: " << idade << std::endl;

    return 0;
}