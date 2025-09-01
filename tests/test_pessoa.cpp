#include "gtest/gtest.h"
#include "pessoa.hpp"
#include <fstream>
#include <stdexcept>
#include "nlohmann/json.hpp"

using namespace std;

// Função auxiliar para criar arquivos temporários de teste
void criarArquivo(const string& caminho, const string& conteudo) {
    ofstream arquivo(caminho);
    arquivo << conteudo;
    arquivo.close();
}

TEST(LerJsonTest, LeituraCorreta) {
    string caminho = "teste_ok.json";
    criarArquivo(caminho, R"({"nome": "João", "idade": 25})");

    Pessoa p = ler_json(caminho);

    EXPECT_EQ(p.nome, "João");
    EXPECT_EQ(p.idade, 25);
}

TEST(LerJsonTest, ArquivoNaoExiste) {
    EXPECT_THROW(ler_json("nao_existe.json"), runtime_error);
}

TEST(LerJsonTest, JsonInvalido) {
    string caminho = "teste_invalido.json";
    criarArquivo(caminho, "isso_nao_e_json");

    EXPECT_THROW(ler_json(caminho), nlohmann::json::parse_error);
}

TEST(LerJsonTest, CamposFaltando) {
    string caminho = "teste_incompleto.json";
    criarArquivo(caminho, R"({"nome": "Maria"})"); // faltando idade

    EXPECT_THROW(ler_json(caminho), nlohmann::json::out_of_range);
}
