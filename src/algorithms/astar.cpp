#include "astar.hpp"


aStar::aStar (std::string src) {
    this->source = src;
}


void aStar::receiveRoot () {
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
            if (this->root->state[i][j] == '$') {
                this->i = i;
                this->j = j;
            }
 		}
    }
    ifs.close();

    // Adiciona o noh raiz a lista de explorados e de a serem verficados
    this->explored.push_back(this->root);
}


void aStar::deleteTree () {
    std::list<Node*>::iterator it;

	if (this->root->n_children != 0) {
		for (int i=0 ; i<this->root->n_children ; i++) {
			this->root->children[i]->deleteChildren();
			delete this->root->children[i];
		}
	}
    delete this->root;
}


int aStar::search () {
    std::vector<int> result;
    this->receiveRoot();
    this->locations = this->root->discoverLocations();
    
    std::cout << this->source << std::endl;

    // Promove uma analise do menor caminho ate a coleta a partir de cada ponto possivel de partida
    while (this->locations.begin() != this->locations.end()) {  // BEGIN WHILE
        // Considera uma das possiveis localizacoes iniciais
        this->root->i = this->locations[this->locations.size()-1][0];
        this->root->j = this->locations[this->locations.size()-1][1];
        this->root->manhattanDistance(this->i, this->j);
        this->manDist[this->root->manDist] = this->root;

        // IMPLEMENTACAO DO aStar
        std::map<int, Node*>::iterator it;
        while (this->manDist.begin() != this->manDist.end()) { // BEGIN_WHILE
            // Pega o estado com o menor numero de movimentos necessarios
            it = this->manDist.begin();

            if ((it->second)->checkState(W) == 1) {
                result.push_back((it->second)->depth); result.push_back((it->second)->loc);
                result.push_back(this->root->i); result.push_back(this->root->j);
                this->results.push_back(result); result.clear();
                goto anotherInitialLocation;
            }

            // Define os filhos do no atual
            (it->second)->defineChildren(&this->explored, this->W);

            // Adiciona os filhos do Node atual nas listas
            for (int i=0 ; i<((it->second)->n_children) ; i++) {
                (it->second)->children[i]->manhattanDistance(this->i, this->j);
                this->manDist[(it->second)->children[i]->manDist] = (it->second)->children[i];
                this->explored.push_back((it->second)->children[i]);
            }

            this->manDist.erase((it->second)->manDist);
        }  // END_WHILE

        // Preparacao do TAD para nova localizacao inicial
        anotherInitialLocation:
        this->locations.pop_back();
        this->deleteTree();
        this->explored.clear();
        this->receiveRoot();
    }  // END WHILE

    this->root->showResult(&this->results);

    return 0;
}
