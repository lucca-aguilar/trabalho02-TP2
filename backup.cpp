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

int copia_restauracao(const string& origem, const string& destino) {
    assert(!origem.empty() && !destino.empty());

    if(copiar_arquivo(origem, destino) == OK) {
        return RESTAURACAO;
    }
    return ERRO;
}

int copia_backup(const string& origem, const string& destino) {
    assert(!origem.empty() && !destino.empty());

    if(copiar_arquivo(origem, destino) == OK) {
        return BACKUP;
    }
    return ERRO;
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

int executar_transferencia(const string& arquivo_origem, const string& arquivo_destino, bool origem_existe, bool destino_existe, bool modo_backup){
    auto func_copia = modo_backup ? copia_backup : copia_restauracao;

    if (modo_backup && !origem_existe && destino_existe) {
        return FAZ_NADA;
    }

    if (!origem_existe) {
        return ERRO;
    }

    if (origem_existe && !destino_existe) {
        return func_copia(arquivo_origem, arquivo_destino);
    }

    if (origem_existe && destino_existe) {
        int comparacao = compara_datas(arquivo_origem, arquivo_destino);
        
        if (comparacao > 0) {
            return func_copia(arquivo_origem, arquivo_destino);
        } else if (comparacao == 0) {
             return FAZ_NADA;
        } else {
            return ERRO; 
        }
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

    assert(getline(arquivo_parm, linha) || linha.empty());

    string origem_dir;
    string destino_dir;
    configurar_diretorios(fazer_backup, origem_dir, destino_dir);
    string arquivo_origem = origem_dir + linha;
    string arquivo_destino = destino_dir + linha;

    bool origem_existe = verificar_existencia_arquivo(arquivo_origem);
    bool destino_existe = verificar_existencia_arquivo(arquivo_destino);

    if(fazer_backup == 1) {
        return executar_transferencia(arquivo_origem, arquivo_destino, origem_existe, destino_existe, true);
    } else {
        return executar_transferencia(arquivo_origem, arquivo_destino, origem_existe, destino_existe, false);
    }
}