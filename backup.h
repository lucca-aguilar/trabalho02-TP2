#ifndef BACKUP_H
#define BACKUP_H

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

#endif