#include "pessoa.hpp"

using json = nlohmann::json;
using namespace std;

void from_json(const json &j, Pessoa &p)
{
    j.at("nome").get_to(p.nome);
    j.at("idade").get_to(p.idade);
}

Pessoa ler_json(const std::string &caminho)
{
    ifstream arquivo(caminho);
    if (!arquivo.is_open())
    {
        throw runtime_error("Erro ao abrir o arquivo");
    }

    json dados;
    try
    {
        dados = json::parse(arquivo);
    }
    catch (const json::parse_error &e)
    {
        throw;
    }

    return dados.get<Pessoa>();
}