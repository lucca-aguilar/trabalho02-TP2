#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "backup.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>

using namespace std;

const string BACKUP_PARM = "Backup.parm";
const string TEST_ARQUIVO = "teste.txt";
const string PENDRIVE_DIR = "pendrive/";
const string HD_DIR = "hd/";
const string HD_ARQUIVO = HD_DIR + TEST_ARQUIVO;
const string PENDRIVE_ARQUIVO = PENDRIVE_DIR + TEST_ARQUIVO;

void criar_arquivo(const string& caminho, const string& conteudo) {
    ofstream ofs(caminho);
    ofs << conteudo;
}

void setup_dirs() {
    system(("mkdir -p " + PENDRIVE_DIR).c_str());
    system(("mkdir -p " + HD_DIR).c_str());
}

void cleanup_dirs() {
    system(("rmdir " + PENDRIVE_DIR).c_str());
    system(("rmdir " + HD_DIR).c_str());
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
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        criar_arquivo(HD_ARQUIVO, "Conteúdo do arquivo do teste da Regra 2.");
        remove(PENDRIVE_ARQUIVO.c_str());
    }

    ~Teste2Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(HD_ARQUIVO.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
        cleanup_dirs();
    }
};

struct Teste3Fixture {
    Teste3Fixture() {
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        criar_arquivo(PENDRIVE_ARQUIVO, "Conteúdo antigo do arquivo do teste da Regra 3.");
        usleep(1000000); 
        criar_arquivo(HD_ARQUIVO, "Conteúdo do arquivo do teste da Regra 3.");
    }

    ~Teste3Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(HD_ARQUIVO.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
        cleanup_dirs();
    }
};

struct Teste4Fixture {
    Teste4Fixture() {
        setup_dirs();
        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        criar_arquivo(HD_ARQUIVO, "Conteúdo do arquivo do teste da Regra 4.");
        criar_arquivo(PENDRIVE_ARQUIVO, "Conteúdo do arquivo do teste da Regra 4.");
    }

    ~Teste4Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(HD_ARQUIVO.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
        cleanup_dirs();
    }
};

// Garante o ambiente para o teste da Regra 6
struct Teste6Fixture {
    Teste6Fixture() {
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        criar_arquivo(HD_ARQUIVO, "Conteúdo do arquivo do teste da Regra 6.");
        remove(PENDRIVE_ARQUIVO.c_str());
    }

    ~Teste6Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(HD_ARQUIVO.c_str());
        cleanup_dirs();
    }
};

// Garante o ambiente para o teste da Regra 10
struct Teste10Fixture {
    Teste10Fixture() {
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        remove(HD_ARQUIVO.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
    }

    ~Teste10Fixture() {
        remove(BACKUP_PARM.c_str());
        cleanup_dirs();
    }
};

// Garante o ambiente para o teste da Regra 11
struct Teste11Fixture {
    Teste11Fixture() {
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        remove(HD_ARQUIVO.c_str());
        criar_arquivo(PENDRIVE_ARQUIVO, "Conteúdo do arquivo do teste da Regra 11.");
    }

    ~Teste11Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
        cleanup_dirs();
    }
};

// Garante o ambiente para o teste da Regra 12
struct Teste12Fixture {
    Teste12Fixture() {
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        remove(HD_ARQUIVO.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
    }

    ~Teste12Fixture() {
        remove(BACKUP_PARM.c_str());
        cleanup_dirs();
    }
};

struct Teste13Fixture {
    Teste13Fixture() {
        setup_dirs();

        criar_arquivo(BACKUP_PARM, TEST_ARQUIVO + "\n");
        remove(HD_ARQUIVO.c_str());
        criar_arquivo(PENDRIVE_ARQUIVO, "Conteúdo do arquivo do teste da Regra 13.");
    }

    ~Teste13Fixture() {
        remove(BACKUP_PARM.c_str());
        remove(HD_ARQUIVO.c_str());
        remove(PENDRIVE_ARQUIVO.c_str());
        cleanup_dirs();
    }
};

TEST_CASE_METHOD(Teste1Fixture, "Teste 1: Arquivo 'Backup.parm' ausente", "[impossivel]") {
    int resultado = executar_espelhamento(1); 
    REQUIRE(resultado == IMPOSSIVEL);
}

TEST_CASE_METHOD(Teste2Fixture, "Teste 2: Backup de arquivo existente no HD para o Pen Drive", "[backup]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == BACKUP);  
}

TEST_CASE_METHOD(Teste3Fixture, "Teste 3: Backup de arquivo existente no HD para o Pen Drive com atualização", "[backup]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == BACKUP);  
}

TEST_CASE_METHOD(Teste4Fixture, "Teste 4: Backup de arquivo existente no HD para o Pen Drive sem necessidade de atualização", "[faz_nada]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == FAZ_NADA);  
}

TEST_CASE_METHOD(Teste6Fixture, "Teste 6: Restauração de arquivo não existente no Pen Drive para o HD", "[erro]") {
    int fazer_backup = 0;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == ERRO);  
}

TEST_CASE_METHOD(Teste10Fixture, "Teste 10: Backup com arquivo ausente no HD e no Pen Drive", "[erro]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == ERRO);  
}

TEST_CASE_METHOD(Teste11Fixture, "Teste 11: Backup de arquivo inexistente no HD e existente no Pen Drive", "[faz_nada]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == FAZ_NADA);  
}

TEST_CASE_METHOD(Teste12Fixture, "Teste 12: Arquivo ausente em ambos HD e Pen Drive", "[erro]") {
    int fazer_backup = 0;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == ERRO);  
}

TEST_CASE_METHOD(Teste13Fixture, "Teste 13: Restauração de arquivo existente no Pen Drive para o HD", "[restauracao]") {
    int fazer_backup = 0;
    int resultado = executar_espelhamento(fazer_backup);

    REQUIRE(resultado == RESTAURACAO);  
}


