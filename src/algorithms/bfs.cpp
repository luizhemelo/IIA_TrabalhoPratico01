#include "bfs.hpp"


BFS::BFS (Node *node, std::string st) {
	root = node;
    source = st;
    w=1;
}


// PARAMETRO: 1 para incluir localizacoes possiveis de inicio / 0 para nao incluir localizacoes possiveis de inicio
void BFS::receiveRoot (int loc) {
    root = new Node(0);
    int i, j, line, column;

    // Recebimento do arquivo de entrada
    std::ifstream ifs (this->source);
    if (!(ifs.is_open())) {
        std::cout << "Erro ao abrir arquivo de origem" << std::endl;
        exit(0);
    }

    // Definicao de numero de linhas/colunas/movimentos
    ifs>>line; ifs>>column; ifs>>this->w;
    this->root->W = this->w;

    // Criacao do no raiz para a arvore
    std::vector<std::vector<char>> matrix(line, std::vector<char>(column));
    this->root->state = matrix;

    // Inclusao do mapa base da empresa
    for (i=0 ; i<line ; i++) {
		for (j=0 ; j<column ; j++) {
			ifs >> this->root->state[i][j];

		}
	}

    // Identifica as possiveis posicoes para inicio do AGV
    if (loc == 1) {
        std::vector<int> vec2(2);
        for (j=0 ; j<column ; j++) {
            if (this->root->state[0][j]=='.' || this->root->state[0][j]=='#') {
                vec2[0]=0; vec2[1]=j;
                this->locations.push_back(vec2);
            }
            if (this->root->state[line-1][j]=='.' || this->root->state[line-1][j]=='#') {
                vec2[0]=line-1; vec2[1]=j;
                this->locations.push_back(vec2);
            }
        }
        for (i=1 ; i<(line-1) ; i++) {
            if (this->root->state[i][0]=='.' || this->root->state[i][0]=='#') {
                vec2[0]=i; vec2[1]=0;
                this->locations.push_back(vec2);
            }
            if (this->root->state[i][column-1]=='.' || this->root->state[i][column-1]=='#') {
                vec2[0]=i; vec2[1]=column-1;
                this->locations.push_back(vec2);
            }
        }
    }

    // Adiciona o noh raiz a lista de explorados e de a serem verficados
    this->frontier.push_back(this->root);

    ifs.close();
}


void BFS::deleteTree () {
    std::list<Node*>::iterator it;

	if (this->root->n_children != 0) {
		for (int i=0 ; i<this->root->n_children ; i++) {
			this->root->children[i]->deleteChildren();
			delete this->root->children[i];
		}
	}

    delete this->root;
}


int BFS::search () {
    this->receiveRoot(1);
    // std::cout << this->source << std::endl;

    // Promove uma analise do menor caminho ate a coleta a partir de cada ponto possivel de partida
    while (this->locations.begin() != this->locations.end()) {  // BEGIN WHILE
        // Considera uma das possiveis localizacoes iniciais
        this->root->i = this->locations[this->locations.size()-1][0];
        this->root->j = this->locations[this->locations.size()-1][1];

        std::list<Node*>::iterator it;
        while (this->frontier.begin() != this->frontier.end()) { // BEGIN_WHILE
            it = this->frontier.begin();

            system("clear");
            for (int i=0 ; i<(*it)->state.size() ; i++) {
                for (int j=0 ; j<(*it)->state[0].size() ; j++) {
                    std::cout << (*it)->state[i][j];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;

            // Checa se o estado atual eh o final
            if ((*it)->checkState(w) == 1) {
                std::cout << (*it)->depth+1 << " " << (*it)->loc << " " << "[";
                std::cout << this->root->i << " , " << this->root->j << "]" << std::endl;
                return 0;
            }

            (*it)->defineChildren(&this->explored, this->w);

            // Adiciona os filhos do Node atual na frontier
            for (int i=0 ; i<((*it)->n_children) ; i++) {
                this->frontier.push_back((*it)->children[i]);
            }
        
            this->explored.push_back(*it);
            this->frontier.pop_front();
        } // END_WHILE

        // Preparacao do TAD para nova localizacao inicial
        this->locations.pop_back();
        this->deleteTree();
        this->receiveRoot(0);
        this->frontier.clear();
        this->explored.clear();
        return 0;
    }  // END WHILE

    return 0;
}
