#ifndef NODE_H
#define NODE_H

#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <list>

struct Node {
	std::vector< std::vector<char> > state;  // Matriz de representacao do estado do Node
    std::vector<Node*> children;  // Lista com filhos do Node
    
    int n_children;  // Numero de filhos do Node
    int depth;  // Profundidade em que se encontra o Node - representa o numero de movimentos feitos pelo AGV
    int i, j;  // Localizacao do AGV no estado representado
    int loc;  // Numero de vezes que o AGV passou em um ponto de localizacao
    int w;  // Numero de vezes que o AGV ainda pode andar sem necessitar de ponto de localizacao

    Node (int _depth=1, int _i=0, int _j=0, int _loc=0, int _w=0);  // Inicializa um novo Node
    std::vector<std::vector<int>> discoverLocations ();  // Identifica as localizacoes iniciais possiveis
    void showResult (std::vector<std::vector<int>> *results);  // Identifica o caminho encontrado com menor numero de movimentos

	int checkState (int W);  // Checa se o estado atual eh o estado final
	int checkExplored (int i, int j, int steps, std::list<Node*> *explored);  // Checa se o no jah foi explorado
	int defineChildren (std::list<Node*> *explored, int W);  // Define os Nodes filhos de em determinado Node atual
	void deleteChildren ();  // Deleta todos os nos filhos
};

#endif
