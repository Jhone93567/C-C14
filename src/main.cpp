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
        cerr << "Erro ao abrir o arquivo" << endl;
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