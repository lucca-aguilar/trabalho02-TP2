#ifndef BACKUP_H
#define BACKUP_H

#include <fstream>
#include <cassert>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <ctime>
#include <cmath>

using namespace std;

#define BACKUP 0
#define RESTAURACAO 1
#define ERRO 2
#define IMPOSSIVEL 3
#define OK 4
#define FAZ_NADA 5

/**
 * Função: executar_espelhamento
 * @brief Executa a lógica principal de espelhamente (backup ou restauração).
 * 
 * Descrição: 
 * A função lê o arquivo 'Backup.parm', compara datas e executa a ação apropriada de acordo com a Tabela de Decisão para cada arquivo.
 * A ausência de 'Backup.parm' ou a falta de arquivos a serem processados resultará em uma mensagem de erro.
 * 
 * Parâmetros:
 * @param fazer_backup - Flag que define modo de operação:
 * 1 para Backup (HD -> Pen Drive)
 * 0 para Restauração (Pen Drive -> HD)
 * 
 * Valor retornado:
 * @return int - Código de retorno da operação:
 * 0 (BACKUP) - Operação de Backup concluída com sucesso.
 * 1 (RESTAURACAO) - Operação de Backup concluída com sucesso. 
 * 2 (ERRO) - Erro na leitura do arquivo 'Backup.parm' ou ausência de arquivos a serem processados.
 * 3 (IMPOSSIVEL) - Operação impossível devido a erros críticos.
 * 5 (FAZ_NADA) - Nenhuma ação necessária (arquivo já está atualizado).
 * 
 * Assertiva de entrada:
 * fazer_backup == 1 || fazer_backup == 0
 * 
 * Assertiva de saída:
 * Retorna OK, ERRO ou IMPOSSIVEL conforme descrito acima.
 */

int executar_espelhamento(int fazer_backup);

/**
 * Função: copiar_arquivo
 * @brief Copia o conteúdo de um arquivo de origem para um arquivo de destino.
 * 
 * Descrição:
 * A função abre o arquivo de origem em modo binário, lê seu conteúdo e escreve no destino.
 * 
 * Parâmetros:
 * @param origem - Caminho do arquivo de origem.
 * @param destino - Caminho onde o arquivo deve ser criado/sobrescrito.
 * 
 * Valor retornado:
 * @return int - Código de retorno da operação:
 * 4 (OK) - Operação concluída com sucesso.
 * 2 (ERRO) - Erro ao abrir ou copiar os arquivos.
 * 
 * Assertiva de entrada:
 * origem != NULL
 * destino != NULL
 * (verificar_existencia_arquivo(origem) == true)
 * 
 * Assertiva de saída:
* Se retorna OK, o arquivo destino existe.
* Se retorna OK, (conteudo_arquivo(origem) == conteudo_arquivo(destino))
 */
int copiar_arquivo(const string& origem, const string& destino);

/**
 * Função: verificar_existencia_arquivo
 * @brief Verifica se um arquivo existe no caminho especificado.
 * 
 * Parâmetros:
 * @param caminho - Caminho do arquivo a ser verificado.
 * 
 * Valor retornado:
 * @return bool - true se o arquivo existe, false caso contrário.
 * 
 * Assertiva de entrada:
 * caminho != NULL
 * 
 * Assertiva de saída:
 * Se retorna true, o arquivo existe no caminho especificado.
 * Se retorna false, o arquivo não existe no caminho especificado.
 */
bool verificar_existencia_arquivo(const string& caminho);

/**
 * Função: configurar_diretorios
 * @brief Configura os diretórios de origem e destino com base no modo de operação.
 * 
 * Parâmetros:
 * @param modo - 1 para Backup (HD -> Pen Drive), 0 para Restauração (Pen Drive -> HD).
 * @param origem_dir - Referência para a string que armazenará o diretório de origem.
 * @param destino_dir - Referência para a string que armazenará o diretório de destino.
 * 
 * Assertiva de entrada:
 * modo == 1 || modo == 0
 * 
 * Assertiva de saída:
 * Se modo == 1, origem_dir == "hd/" e destino_dir == "pendrive/"
 * Se modo == 0, origem_dir == "pendrive/" e destino_dir == "hd/"
 */
void configurar_diretorios(int modo, string& origem_dir, string& destino_dir);

/**
 * Função: simular_data
 * @brief Altera a data de modificação de um arquivo para torná-lo mais recente.
 * 
 * Descrição:
 * Garante que o arquivo especificado tenha um timestamp mais recente
 * que outro, ou que o sistema. Usa API do sistema operacional (utimes ou equivalente).
 * 
 * Parâmetros:
 * @param caminho - Caminho do arquivo cuja data será alterada.
 * 
 * Valor retornado:
 * @return int - Código de retorno da operação:
 * 4 (OK) - Operação concluída com sucesso.
 * 2 (ERRO) - Erro ao alterar a data do arquivo.
 * 
 * Assertiva de entrada:
 * caminho != NULL
 * (verificar_existencia_arquivo(caminho) == true)
 * 
 * Assertiva de saída:
 * Se retorna OK, a data de modificação do arquivo foi alterada com sucesso.
 * Se retorna OK, o arquivo existe no caminho especificado.
 */
int simular_data(string& caminho);

/**
 * Função: compara_datas
 * @brief Compara as datas de modificação de dois arquivos.
 * 
 * Descrição:
 * Retorna a diferença em segundos entre as datas de modificação dos arquivos.
 * 
 * Parâmetros:
 * @param caminho1 - Caminho do primeiro arquivo.
 * @param caminho2 - Caminho do segundo arquivo.
 * 
 * Valor retornado:
 * @return int - Diferença em segundos entre as datas:
 * > 0 se o primeiro arquivo é mais recente,
 * < 0 se o segundo arquivo é mais recente,
 * 0 se ambos têm a mesma data ou se algum arquivo não existe.
 * 
 * Assertiva de entrada:
 * caminho1 != NULL
 * caminho2 != NULL
 * 
 * Assertiva de saída:
 * Se retorna > 0, (data_modificacao(caminho1) > data_modificacao(caminho2))
 * Se retorna < 0, (data_modificacao(caminho1) < data_modificacao(caminho2))
 * Se retorna 0, (data_modificacao(caminho1) == data_modificacao(caminho2)) ou algum dos arquivos não existe.
 */
int compara_datas(const string& caminho1, const string& caminho2);

/**
 * Função: executar_backup
 * @brief Executa a lógica de backup entre dois arquivos.
 * 
 * Descrição:
 * Compara a existência e datas dos arquivos de origem e destino para decidir se deve copiar o arquivo.
 * 
 * Parâmetros:
 * @param arquivo_origem - Caminho do arquivo de origem.
 * @param arquivo_destino - Caminho do arquivo de destino.
 * @param origem_existe - Flag indicando se o arquivo de origem existe.
 * @param destino_existe - Flag indicando se o arquivo de destino existe.
 * 
 * Valor retornado:
 * @return int - Código de retorno da operação:
 * 0 (BACKUP) - Backup realizado com sucesso.
 * 2 (ERRO) - Erro na operação de backup.
 * 5 (FAZ_NADA) - Nenhuma ação necessária (arquivo já está atualizado).
 * 
 * Assertiva de entrada:
 * arquivo_origem != NULL
 * arquivo_destino != NULL
 * 
 * Assertiva de saída:
 * Se retorna BACKUP, (conteudo_arquivo(arquivo_origem) == conteudo_arquivo(arquivo_destino))
 * Se retorna FAZ_NADA, (conteudo_arquivo(arquivo_origem) == conteudo_arquivo(arquivo_destino)) ou (origem_existe == false) or (destino_existe == false)            
 * Se retorna ERRO, (conteudo_arquivo(arquivo_origem) != conteudo_arquivo(arquivo_destino)) and (origem_existe == false) and (destino_existe == false)          
 */
int executar_backup(const string& arquivo_origem, const string& arquivo_destino, bool origem_existe, bool destino_existe);

/**
 * Função: executar_restauracao
 * @brief Executa a lógica de restauração entre dois arquivos.      
 * 
 * Descrição:
 * Compara a existência dos arquivos de origem e destino para decidir se deve copiar o arquivo.
 * 
 * Parâmetros:
 * @param arquivo_origem - Caminho do arquivo de origem.
 * @param arquivo_destino - Caminho do arquivo de destino.
 * @param origem_existe - Flag indicando se o arquivo de origem existe.
 * @param destino_existe - Flag indicando se o arquivo de destino existe.
 * 
 * Valor retornado:
 * @return int - Código de retorno da operação:
 * 1 (RESTAURACAO) - Restauração realizada com sucesso.
 * 2 (ERRO) - Erro na operação de restauração.
 * 
 * Assertiva de entrada:
 * arquivo_origem != NULL
 * arquivo_destino != NULL
 * 
 * Assertiva de saída:
 * Se retorna RESTAURACAO, (conteudo_arquivo(arquivo_origem) == conteudo_arquivo(arquivo_destino))
 * Se retorna ERRO, (conteudo_arquivo(arquivo_origem) != conteudo_arquivo(arquivo_destino)) and (origem_existe == false) and (destino_existe == false) or (origem_existe == false) and (destino_existe == true)
 */
int executar_restauracao(const string& arquivo_origem, const string& arquivo_destino, bool origem_existe, bool destino_existe);
#endif // BACKUP_H