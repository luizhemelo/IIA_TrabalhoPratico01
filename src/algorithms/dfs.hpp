#ifndef DFS_H
#define DFS_H

#include "../node/node.hpp"

struct DFS {
	std::vector<std::vector<int>> locations;  // Localizacoes possiveis para inicio do AGV
	std::vector<std::vector<int>> results;  // Resultados obtidos para cada uma das posicoes iniciais
	std::list<Node*> frontier;  // Fila de execucao, que organiza as operacoes
	std::list<Node*> explored;  // Lista de estados jah verificados

	std::string source;  // Arquivo de entrada para a aplicacao
	Node* root;  // Node raiz da arvore de busca para o DFS
	int W;  // Numero maximo de movimentos possiveis
	
	DFS (std::string src);  // Inicia um nova dependencia para execucao do DFS - parametro: nome arquivo de entrada

	void receiveRoot ();   // Recebe o estado inicial, que correspondera ao Node raiz
	void deleteTree ();  // Deleta o Node raiz e toda a arvore por ele gerada
	int runDFS (Node* node);  // Executa o algoritmo de recursao do DFS
	int search ();  // Executa o algoritmo, criando uma arvore e buscando o estado final entre os possiveis estados
};

#endif
