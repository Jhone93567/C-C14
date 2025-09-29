#pragma once

#include "nlohmann/json.hpp"
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

struct Pessoa
{
    string nome;
    int idade;
};

Pessoa ler_json(const string &caminho);

void from_json(const nlohmann::json &j, Pessoa &p);