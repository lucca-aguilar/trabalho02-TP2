#include "backup.h"

using namespace std;

bool verificar_existencia_arquivo(const string& caminho) {
    assert(!caminho.empty());
    ifstream arquivo(caminho);
    bool existencia = arquivo.is_open();
    arquivo.close();

    return existencia;
}

void configurar_diretorios(int modo, string& origem_dir, string& destino_dir) {
    if(modo == 1) {
            origem_dir = "hd/";
            destino_dir = "pendrive/";
        } else {
            origem_dir = "pendrive/";
            destino_dir = "hd/";
        }
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

int simular_data(const string& caminho) {
    assert(!caminho.empty());
    if(system(("touch " + caminho).c_str()) == 0) {
        return OK;
    }
    return ERRO;
}

int executar_espelhamento(int fazer_backup) {
    assert(fazer_backup == 0 || fazer_backup == 1);
    
    ifstream arquivo_parm("Backup.parm");
    if (!arquivo_parm.is_open()) {
        return IMPOSSIVEL;
    }

    string linha;
    if(getline(arquivo_parm, linha)) {
        string origem_dir;
        string destino_dir;

        configurar_diretorios(fazer_backup, origem_dir, destino_dir);

        string arquivo_origem = origem_dir + linha;
        string arquivo_destino = destino_dir + linha;

        bool origem_existe = verificar_existencia_arquivo(arquivo_origem);
        bool destino_existe = verificar_existencia_arquivo(arquivo_destino);

        if(fazer_backup == 1) {
            if(!origem_existe && !destino_existe) {
                return ERRO;
            }

            if(origem_existe && !destino_existe) {
                if (copiar_arquivo(arquivo_origem, arquivo_destino) == OK) return BACKUP;
            }

            if(!origem_existe && destino_existe) {
                return FAZ_NADA;
            }

            return BACKUP;
        } else {
            if((!origem_existe && !destino_existe) || (!origem_existe && destino_existe)) {
                return ERRO;
            } 
        }

        return RESTAURACAO;
    };
}