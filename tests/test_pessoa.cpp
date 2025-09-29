#include "gtest/gtest.h"
#include "pessoa.hpp"
#include <stdexcept>
#include <vector>
#include <cstdio>

using namespace std;
using json = nlohmann::json;

class LerJsonTest : public ::testing::Test {
protected:
    // Chamado antes de cada teste
    void SetUp() override {
        // Limpa a lista de arquivos de testes anteriores, se houver
        arquivos_de_teste.clear();
    }

    // Chamado depois de cada teste
    void TearDown() override {
        // Remove todos os arquivos criados durante o teste
        for (const auto& caminho : arquivos_de_teste) {
            remove(caminho.c_str());
        }
    }

    // Função auxiliar para criar arquivos e registrar para limpeza
    void criarArquivo(const string& caminho, const string& conteudo) {
        ofstream arquivo(caminho);
        ASSERT_TRUE(arquivo.is_open()); // Garante que o arquivo foi criado
        arquivo << conteudo;
        arquivo.close();
        arquivos_de_teste.push_back(caminho);
    }

    vector<string> arquivos_de_teste;
};

// Cenarios de Sucesso

TEST_F(LerJsonTest, LeituraCorreta) {
    const string caminho = "teste_ok.json";
    criarArquivo(caminho, R"({"nome": "João", "idade": 25})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.nome, "João");
    EXPECT_EQ(p.idade, 25);
}

TEST_F(LerJsonTest, OrdemDosCamposTrocada) {
    const string caminho = "teste_ordem.json";
    criarArquivo(caminho, R"({"idade": 30, "nome": "Maria"})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.nome, "Maria");
    EXPECT_EQ(p.idade, 30);
}

TEST_F(LerJsonTest, CamposExtrasSaoIgnorados) {
    const string caminho = "teste_extras.json";
    criarArquivo(caminho, R"({"nome": "Carlos", "idade": 40, "cidade": "SP"})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.nome, "Carlos");
    EXPECT_EQ(p.idade, 40);
}

TEST_F(LerJsonTest, NomeComEspacos) {
    const string caminho = "teste_espacos.json";
    criarArquivo(caminho, R"({"nome": "Ana Clara", "idade": 22})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.nome, "Ana Clara");
}

TEST_F(LerJsonTest, IdadeZero) {
    const string caminho = "teste_idade_zero.json";
    criarArquivo(caminho, R"({"nome": "Bebê", "idade": 0})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.idade, 0);
}

TEST_F(LerJsonTest, EspacamentoNoJson) {
    const string caminho = "teste_whitespace.json";
    criarArquivo(caminho, "  { \n \"nome\" : \n \"Pedro\" \t , \n \"idade\":50 \n }  ");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.nome, "Pedro");
    EXPECT_EQ(p.idade, 50);
}

// Cenarios de Erro de Arquivo

TEST_F(LerJsonTest, ArquivoNaoExiste) {
    EXPECT_THROW(ler_json("arquivo_fantasma.json"), runtime_error);
}

TEST_F(LerJsonTest, ArquivoVazio) {
    const string caminho = "teste_vazio.json";
    criarArquivo(caminho, "");
    EXPECT_THROW(ler_json(caminho), json::parse_error);
}

// Cenarios de Erro de Formato JSON

TEST_F(LerJsonTest, JsonInvalidoSintaxe) {
    const string caminho = "teste_invalido.json";
    criarArquivo(caminho, R"({"nome": "Invalido", "idade": 30,})"); // Virgula extra
    EXPECT_THROW(ler_json(caminho), json::parse_error);
}

TEST_F(LerJsonTest, NaoEhUmObjetoJson) {
    const string caminho = "teste_nao_objeto.json";
    criarArquivo(caminho, R"(["nome", "idade"])"); // Eh um array
    EXPECT_THROW(ler_json(caminho), json::type_error);
}

TEST_F(LerJsonTest, TextoSimplesNaoEhJson) {
    const string caminho = "teste_texto.json";
    criarArquivo(caminho, "apenas texto normal");
    EXPECT_THROW(ler_json(caminho), json::parse_error);
}

TEST_F(LerJsonTest, JsonContendoApenasNull) {
    const string caminho = "teste_null.json";
    criarArquivo(caminho, "null");
    EXPECT_THROW(ler_json(caminho), json::type_error);
}

// Cenarios de Erro de Conteudo (Campos Faltando ou Tipos Errados)

TEST_F(LerJsonTest, CampoNomeFaltando) {
    const string caminho = "teste_sem_nome.json";
    criarArquivo(caminho, R"({"idade": 30})");
    EXPECT_THROW(ler_json(caminho), json::out_of_range);
}

TEST_F(LerJsonTest, CampoIdadeFaltando) {
    const string caminho = "teste_sem_idade.json";
    criarArquivo(caminho, R"({"nome": "Maria"})");
    EXPECT_THROW(ler_json(caminho), json::out_of_range);
}

TEST_F(LerJsonTest, AmbosCamposFaltando) {
    const string caminho = "teste_sem_nada.json";
    criarArquivo(caminho, R"({})");
    EXPECT_THROW(ler_json(caminho), json::out_of_range);
}

TEST_F(LerJsonTest, TipoIncorretoParaNome) {
    const string caminho = "teste_nome_tipo_errado.json";
    criarArquivo(caminho, R"({"nome": 123, "idade": 30})");
    EXPECT_THROW(ler_json(caminho), json::type_error);
}

TEST_F(LerJsonTest, TipoIncorretoParaIdade) {
    const string caminho = "teste_idade_tipo_errado.json";
    criarArquivo(caminho, R"({"nome": "José", "idade": "trinta"})");
    EXPECT_THROW(ler_json(caminho), json::type_error);
}

TEST_F(LerJsonTest, CampoNomeEhNull) {
    const string caminho = "teste_nome_null.json";
    criarArquivo(caminho, R"({"nome": null, "idade": 25})");
    EXPECT_THROW(ler_json(caminho), json::type_error);
}

TEST_F(LerJsonTest, CampoIdadeEhNull) {
    const string caminho = "teste_idade_null.json";
    criarArquivo(caminho, R"({"nome": "Ana", "idade": null})");
    EXPECT_THROW(ler_json(caminho), json::type_error);
}

// Cenarios de Limite e Casos Extremos

TEST_F(LerJsonTest, IdadeNegativa) {
    // A função deve ler, mas a logica de negocio poderia validar depois
    const string caminho = "teste_idade_negativa.json";
    criarArquivo(caminho, R"({"nome": "Congelado", "idade": -10})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.idade, -10);
}

TEST_F(LerJsonTest, IdadeComoPontoFlutuante) {
    const string caminho = "teste_idade_float.json";
    // A biblioteca nlohmann/json por padrao vai trocar o valor para int.
    // Se a precisao fosse importante, o tipo da idade deveria ser float ou double.
    criarArquivo(caminho, R"({"nome": "Quebrado", "idade": 25.9})");
    Pessoa p = ler_json(caminho);
    EXPECT_EQ(p.idade, 25);
}

TEST_F(LerJsonTest, CaseSensitive) {
    const string caminho = "teste_case.json";
    // "Nome" com 'N' maiusculo não é "nome".
    criarArquivo(caminho, R"({"Nome": "Case", "idade": 30})");
    EXPECT_THROW(ler_json(caminho), json::out_of_range);
}