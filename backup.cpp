#include "backup.h"
#include <fstream>
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

int executar_espelhamento(int fazer_backup) {
    assert(fazer_backup == 0 || fazer_backup == 1);
    
    ifstream arquivo_parm("Backup.parm");
    if (!arquivo_parm.is_open()) {
        return IMPOSSIVEL;
    }

    string linha;
    if(getline(arquivo_parm, linha)) {
        string arquivo_origem = "HD_DIR/" + linha;
        string arquivo_destino = "PENDRIVE_DIR/" + linha;

        if(fazer_backup == 1) {
            ifstream src(arquivo_origem, ios::binary);
            ifstream dst(arquivo_destino, ios::binary);

            if(src.is_open() && dst.is_open()) {
                dst >> src.rdbuf();
                return OK;
            }
        }
    }

    return OK;
}