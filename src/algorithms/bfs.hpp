#ifndef BFS_H
#define BFS_H

#include "../node/node.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

struct BFS {
	std::vector< std::vector<int> > locations;  // Localizacoes possiveis para inicio do AGV
	std::list<Node*> frontier;  // Fila de execucao, que organiza as operacoes
	std::list<Node*> explored;  // Lista de estados jah verificados
	std::string source;  // Arquivo de entrada para a aplicacao
	Node* root;  // Node raiz da arvore de busca para o BFS
	int w;  // Numero maximo de movimentos possiveis / Pontos de localizacao utilizados
	
	BFS (Node *node, std::string st);  // Inicia um nova dependencia para execucao do BFS
	void receiveRoot (int loc);   // Recebe o estado inicial, que correspondera ao Node raiz
	void deleteTree ();  // Deleta o Node raiz e toda a arvore por ele gerada
	int search ();  // Executa o algoritmo, criando uma arvore e buscando o estado final entre os possiveis estados
};

#endif
