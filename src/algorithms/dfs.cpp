#include "dfs.hpp"


DFS::DFS (std::string src) {
    this->source = src;
}


void DFS::receiveRoot () {
    int i, j, line, column;

    // Recebimento do arquivo de entrada
    std::ifstream ifs (this->source);
    if (!(ifs.is_open())) {
        std::cout << "Erro ao abrir arquivo de origem" << std::endl;
        exit(0);
    }

    // Criacao do no raiz
    this->root = new Node();

    // Definicao de numero de linhas/colunas/movimentos
    ifs>>line; ifs>>column;
    ifs>>this->W; this->root->w=this->W;

    // Criacao do no raiz para a arvore
    std::vector<std::vector<char>> matrix(line, std::vector<char>(column));
    this->root->state = matrix;

    // Inclusao do mapa base da empresa
    for (i=0 ; i<line ; i++) {
		for (j=0 ; j<column ; j++) {
			ifs >> this->root->state[i][j];

		}
    }
    ifs.close();

    // Adiciona o noh raiz a lista de explorados e de a serem verficados
    this->explored.push_back(this->root);
    this->frontier.push_back(this->root);
}


void DFS::deleteTree () {
    std::list<Node*>::iterator it;

	if (this->root->n_children != 0) {
		for (int i=0 ; i<this->root->n_children ; i++) {
			this->root->children[i]->deleteChildren();
			delete this->root->children[i];
		}
	}
    delete this->root;
}


int DFS::runDFS (Node* node) {
    // IMPLEMENTACAO DO DFS
}


int DFS::search () {
    std::vector<int> result;
    this->receiveRoot();
    this->locations = this->root->discoverLocations();
    
    std::cout << this->source << std::endl;

    // Promove uma analise do menor caminho ate a coleta a partir de cada ponto possivel de partida
    while (this->locations.begin() != this->locations.end()) {  // BEGIN WHILE
        // Considera uma das possiveis localizacoes iniciais
        this->root->i = this->locations[this->locations.size()-1][0];
        this->root->j = this->locations[this->locations.size()-1][1];

        // IMPLEMENTACAO DO DFS

        // Preparacao do TAD para nova localizacao inicial
        anotherInitialLocation:
        this->locations.pop_back();
        this->deleteTree();
        this->explored.clear();
        this->frontier.clear();
        this->receiveRoot();
    }  // END WHILE

    this->root->showResult(&this->results);

    return 0;
}
