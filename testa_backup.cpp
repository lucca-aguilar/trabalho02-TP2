#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "backup.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

const string BACKUP_PARM = "Backup.parm";

// Garante que não haverá arquivo 'Backup.parm' antes do Teste 1
struct Teste1Fixture {
    Teste1Fixture() {
        remove(BACKUP_PARM.c_str());
    }
};

TEST_CASE_METHOD(Teste1Fixture, "Teste 1: Arquivo 'Backup.parm' ausente", "[impossivel]") {
    int fazer_backup = 1;
    int resultado = executar_espelhamento(1); 
    REQUIRE(resultado == IMPOSSIVEL);
}

