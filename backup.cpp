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

int compara_datas(const string& caminho1, const string& caminho2) {
    assert(!caminho1.empty() && !caminho2.empty());

    struct stat stat1;
    struct stat stat2;

    if(stat(caminho1.c_str(), &stat1) != 0 || stat(caminho2.c_str(), &stat2) != 0) {
        return 0; 
    }

    if(stat1.st_mtime > stat2.st_mtime) {
        return 1; 
    } else if(stat1.st_mtime < stat2.st_mtime) {
        return -1; 
    } else {
        return 0; 
    }
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

            if(origem_existe && destino_existe) {
                if(compara_datas(arquivo_origem, arquivo_destino) > 0) {
                    if(copiar_arquivo(arquivo_origem, arquivo_destino) == OK) {
                        return BACKUP;
                    } else {
                        return ERRO;
                    }
                } else {
                    return FAZ_NADA;
                }
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