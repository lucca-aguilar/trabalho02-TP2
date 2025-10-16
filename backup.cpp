#include "backup.h"

using namespace std;

bool verificar_existencia_arquivo(const string& caminho) {
    assert(!caminho.empty());
    ifstream arquivo(caminho);
    bool existencia = arquivo.is_open();
    arquivo.close();

    return existencia;
}

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
        if(fazer_backup == 1) {
            string arquivo_origem = "hd/" + linha;
            string arquivo_destino = "pendrive/" + linha;

            bool hd_existe = verificar_existencia_arquivo(arquivo_origem);
            bool pendrive_existe = verificar_existencia_arquivo(arquivo_destino);

            if(!hd_existe && !pendrive_existe) {
                return ERRO;
            }

            if(hd_existe && !pendrive_existe) {
                return copiar_arquivo(arquivo_origem, arquivo_destino);
            }
        } else {
            string arquivo_origem = "pendrive/" + linha;
            string arquivo_destino = "hd/" + linha;

            bool hd_existe = verificar_existencia_arquivo(arquivo_origem);
            bool pendrive_existe = verificar_existencia_arquivo(arquivo_destino);

            if(!hd_existe && !pendrive_existe) {
                return ERRO;
            } 
        }
    }

    return OK;
}