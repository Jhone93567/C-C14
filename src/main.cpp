#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main()
{
    std::ifstream arquivo("../teste.json");

    if (!arquivo.is_open())
    {
        std::cerr << "TUDO ERRADO!!" << std::endl;
        return 1;
    }

    json dados;

    arquivo >> dados;

    std::string nome = dados["name"];

    int idade = dados["age"];

    std::cout << "Nome: " << nome << std::endl;
    std::cout << "Idade: " << idade << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

int main()
{
    ifstream arquivo("../teste.json");

    if (!arquivo.is_open())
    {
        cerr << "TUDO ERRADOO!!!" << endl;
        return 1;
    }

    json dados;

    arquivo >> dados;

    try
    {
        string nome = dados["nome"];
    
        int idade = dados["idade"];
        
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}