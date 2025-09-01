#include "pessoa.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;
using namespace std;

Pessoa ler_json(const string& caminho) {
    ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo");
    }

    json dados;
    arquivo >> dados;

    Pessoa p;
    p.nome = dados.at("nome");
    p.idade = dados.at("idade");
    return p;
}
