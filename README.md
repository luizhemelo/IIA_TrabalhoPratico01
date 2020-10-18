# Trabalho Prático 01
#### Introdução à Inteligência Artificial - 2020/1

Repositório com arquivos e códigos para implementação e execução do Trabalho Prático 01 da disciplina de Introdução à Inteligência Artificial do semestre 2020/1.

Diretórios:
  - '_node_' - códigos da estrutura base da árvore de busca 
  - "_algorithms_' - códigos de todos os algoritmos requeridos pelo Trabalho

Para executar qualquer código/comando, execute no diretório '_./src_'.

Para compilar:

```sh
$ make
```
Para rodar todos os inputs disponibilizados junto com o Trabalho de uma única vez:
```sh
$ bash test_bfs.sh
$ bash test_dfs.sh
$ bash test_ids.sh
$ bash test_a_star.sh
```

Para executar um teste unitário com algum algoritmo específico:
```sh
$ ./algorithms/agv <nome_do_algortimo> <diretorio_do_input>
```
