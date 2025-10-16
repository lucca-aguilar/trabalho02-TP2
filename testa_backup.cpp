#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "backup.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

const string BACKUP_PARM = "Backup.parm";
const string TEST_ARQUIVO = "teste.txt";
const string PENDRIVE_DIR = "pendrive/";
const string HD_DIR = "hd/";
const string TEST_ARQUIVO_DESTINO = PENDRIVE_DIR + TEST_ARQUIVO;
const string TEST_ARQUIVO_ORIGEM = HD_DIR + TEST_ARQUIVO;

void criar_arquivo(const string& caminho, const string& conteudo) {
    ofstream ofs(caminho);
    ofs << conteudo;
}

// Garante o ambiente para o teste da Regra 1
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

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        criar_arquivo(TEST_ARQUIVO_ORIGEM, "Conteúdo do arquivo do teste da Regra 2.");
        remove(TEST_ARQUIVO_DESTINO.c_str());
    }

    ~Teste2Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(TEST_ARQUIVO_ORIGEM.c_str());
        remove(TEST_ARQUIVO_DESTINO.c_str());
        system(("rmdir " + PENDRIVE_DIR).c_str());
        system(("rmdir " + HD_DIR).c_str());
    }
};

struct Teste10Fixture {
    Teste10Fixture() {
        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        remove(TEST_ARQUIVO_DESTINO.c_str());
        remove(TEST_ARQUIVO_ORIGEM.c_str());
    }

    ~Teste10Fixture() {
        remove(BACKUP_PARM.c_str());
    }
};

// Garante o ambiente para o teste da Regra 12
struct Teste12Fixture {
    Teste12Fixture() {
        system(("mkdir -p " + HD_DIR).c_str());
        system(("mkdir -p " + PENDRIVE_DIR).c_str());

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        remove(TEST_ARQUIVO_DESTINO.c_str());
        remove(TEST_ARQUIVO_ORIGEM.c_str());
    }

    ~Teste12Fixture() {
        remove(BACKUP_PARM.c_str());
        system(("rmdir " + PENDRIVE_DIR).c_str());
        system(("rmdir " + HD_DIR).c_str());
    }
};

TEST_CASE_METHOD(Teste1Fixture, "Teste 1: Arquivo 'Backup.parm' ausente", "[impossivel]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(1); 
    REQUIRE(resultado == IMPOSSIVEL);
}

TEST_CASE_METHOD(Teste2Fixture, "Teste 2: Backup de arquivo existente no HD para o Pen Drive", "[backup]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == OK);  
}

TEST_CASE_METHOD(Teste10Fixture, "Teste 10: Backup com arquivo ausente no HD e no Pen Drive", "[erro]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == ERRO);  
}

TEST_CASE_METHOD(Teste12Fixture, "Teste 12: Arquivo ausente em ambos HD e Pen Drive", "[erro]") {
    int fazer_backup = 0;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == ERRO);  
}

