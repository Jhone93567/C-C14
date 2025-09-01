#pragma once
#include <string>

using namespace std;

struct Pessoa {
    string nome;
    int idade;
};

Pessoa ler_json(const string& caminho);
