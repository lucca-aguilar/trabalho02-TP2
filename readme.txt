
TRABALHO 2: SISTEMA DE ESPELHAMENTO DE ARQUIVOS
Técnicas de Programação 2 (CIC0198)

Autor: Lucca Santos Aguilar
Matrícula: 241024221

Este projeto implementa um sistema de backup e restauração de arquivos baseado na Tabela de Decisão (Testes de Caixa Fechada), seguindo a metodologia de Desenvolvimento Orientado a Testes (TDD). O histórico de commits está disponível no diretório '.git'.


1. PRÉ-REQUISITOS
Para compilar e executar o projeto, você deve ter instalado no seu ambiente GNU/Linux (como Ubuntu):
1.  Compilador C++: g++ (versão C++17 ou superior).
2.  Ferramentas de Build: make.
3.  Bibliotecas de Teste: O projeto usa Catch2, que está amalgamado.
4.  Ferramentas de Qualidade: Doxygen, cpplint, cppcheck, valgrind.
Para gerar a documentação Doxygen, o arquivo 'Doxyfile' deve estar presente na raiz.


2. INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO
Todos os comandos devem ser executados na raiz do diretório do projeto.
A. Compilação (Build)
O Makefile padrão compila o binário de testes ('testa_backup').
    $ make all
B. Execução dos Testes Unitários
Roda o binário de testes ('testa_backup') gerado para verificar a funcionalidade das Regras (Colunas da Tabela de Decisão).
    $ make test
C. Verificação de Cobertura de Código (Obrigatório)
Este comando compila o código com as flags '-fprofile-arcs' e '-ftest-coverage' e, após rodar o executável, gera o relatório 'gcov' para comprovar a cobertura de 80% do código por módulo.
    $ make gcov


3. FERRAMENTAS DE QUALIDADE (CHECKLISTS)
Os comandos abaixo garantem que o código segue os padrões exigidos (Google Style Guide) e que não há problemas de memória.
A. Verificação de Estilo (CppLint)
Verifica se o código segue o padrão de codificação (Google Style Guide).
    $ make cpplint
B. Verificação Estática (CppCheck)
Verifica o código em busca de erros lógicos, de sintaxe e problemas de alocação.
    $ make cppcheck
C. Verificação Dinâmica (Valgrind)
Roda os testes sob o Valgrind para detectar vazamentos e acessos indevidos à memória.
    $ make valgrind


4. Geração de Documentação (Doxygen)
Gera a documentação do código-fonte (Assertivas, Funções, etc.) em HTML e LaTeX. O arquivo 'Doxyfile' deve estar configurado na raiz.
    $ make doc
Para visualizar: Abra o arquivo 'html/index.html' no seu navegador.


5. LIMPEZA
Remove todos os arquivos gerados (binários, objetos, relatórios de cobertura e diretórios Doxygen).
    $ make clean