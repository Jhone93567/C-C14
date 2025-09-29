#include "pessoa.hpp"
#include <iostream>
#include <filesystem>

using namespace std;

const string NOME_ARQUIVO_CONFIG = "teste.json";

int main(int argc, char* argv[]) {
    if (argc < 1) {
        cerr << "Erro: Não foi possível determinar o caminho do executável." << endl;
        return 1;
    }
    
    filesystem::path caminho_executavel = argv[0];
    filesystem::path diretorio_executavel = caminho_executavel.parent_path();
    filesystem::path caminho_do_arquivo = diretorio_executavel / NOME_ARQUIVO_CONFIG;

    try {
        Pessoa p = ler_json(caminho_do_arquivo.string());
        cout << "Nome: " << p.nome << endl;
        cout << "Idade: " << p.idade << endl;
    } catch (const exception& e) {
        cerr << "Erro ao processar o arquivo '" << caminho_do_arquivo.string() << "': " << e.what() << endl;
        return 1;
    }

    return 0;
}