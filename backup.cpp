#include "backup.h"

using namespace std;

int copiar_arquivo(const string& origem, const string& destino) {
    assert(!origem.empty() && !destino.empty());
    
    ifstream src(origem, ios::binary);
    ofstream dst(destino, ios::binary);

    if (!src.is_open() || !dst.is_open()) {
        return ERRO;
    }

    dst << src.rdbuf();
    return OK;
}

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
            ifstream src_check(arquivo_origem);
            ifstream dst_check(arquivo_destino);

            if(src_check.is_open() && !dst_check.is_open()) {
                int resultado = copiar_arquivo(arquivo_origem, arquivo_destino);

                src_check.close();
                dst_check.close();

                return resultado;
            }
        }
    }

    return OK;
}