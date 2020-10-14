#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <list>

struct Node {
	std::vector< std::vector<char> > state;  // Estado do Node
	std::vector<Node*> children;  // Filhos do Node
	int n_children;  // Numero de filhos do Node
	int depth;  // Profundidade em que se encontra o Node
	int i, j;  // Localizacao do AGV no estado representado
	int loc;  // Numero de vezes que o AGV passou em um ponto de localizacao
	int W;  // Numero de vezes que o AGV ainda pode andar sem necessitar de ponto de localizacao

	Node (int dep);  // Inicializa um novo Node
	int checkState (int w);  // Checa se o estado atual eh o estado final
	int checkExplored (std::list<Node*> *explored);  // Checa se o no a ser adicionado jah esta presenta na lista de estados explorados
	int defineChildren (std::list<Node*> *explored, int w);  // Define os Nodes filhos de em determinado Node atual
	void deleteChildren ();  // Deleta todos os nos filhos
};

#endif
