#ifndef BACKUP_H
#define BACKUP_H

#include <fstream>
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

#define OK 0
#define ERRO 1
#define IMPOSSIVEL 2

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
 * 0 (OK) - Operação concluída com sucesso.
 * 1 (ERRO) - Erro na leitura do arquivo 'Backup.parm' ou ausência de arquivos a serem processados.
 * 2 (IMPOSSIVEL) - Operação impossível devido a erros críticos.
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
 * 0 (OK) - Operação concluída com sucesso.
 * 1 (ERRO) - Erro ao abrir ou copiar os arquivos.
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
 */
bool verificar_existencia_arquivo(const string& caminho);

#endif