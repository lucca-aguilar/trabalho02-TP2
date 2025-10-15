#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "backup.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

const string BACKUP_PARM = "Backup.parm";
const string TEST2_ARQUIVO = "teste_regra2.txt";
const string PENDRIVE_DIR = "pendrive/";
const string HD_DIR = "hd/";
const string TEST2_ARQUIVO_DESTINO = PENDRIVE_DIR + TEST2_ARQUIVO;
const string TEST2_ARQUIVO_ORIGEM = HD_DIR + TEST2_ARQUIVO;

void criar_arquivo(const string& caminho, const string& conteudo) {
    ofstream ofs(caminho);
    ofs << conteudo;
}

// Garante que não haverá arquivo 'Backup.parm' antes do Teste 1
struct Teste1Fixture {
    Teste1Fixture() {
        remove(BACKUP_PARM.c_str());
    }
};

// Garante o ambiente para o teste da Regra 2
struct Teste2Fixture {
    Teste2Fixture() {
        system(("mkdir -p " + PENDRIVE_DIR).c_str());
        system(("mkdir -p " + HD_DIR).c_str());

        criar_arquivo(BACKUP_PARM, TEST2_ARQUIVO + "\n");
        criar_arquivo(TEST2_ARQUIVO_ORIGEM, "Conteúdo do arquivo do teste da Regra 2.");
        remove(TEST2_ARQUIVO_DESTINO.c_str());
    }
};

TEST_CASE_METHOD(Teste1Fixture, "Teste 1: Arquivo 'Backup.parm' ausente", "[impossivel]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(1); 
    REQUIRE(resultado == IMPOSSIVEL);
}

TEST_CASE_METHOD(Teste2Fixture, "Teste 2: Backup de arquivo existente no HD para o Pen Drive", "[backup]") {
    int fazer_backup = 1;
    REQUIRE(!ifstream(TEST2_ARQUIVO_DESTINO).good());

    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == OK);
    REQUIRE(ifstream(TEST2_ARQUIVO_DESTINO).good());    
}

