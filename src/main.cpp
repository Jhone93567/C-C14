#include "pessoa.hpp"
#include <iostream>

using namespace std;

int main() {
    try {
        Pessoa p = ler_json("../teste.json");
        cout << "Nome: " << p.nome << endl;
        cout << "Idade: " << p.idade << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
