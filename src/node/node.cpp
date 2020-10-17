#include "node.hpp"


Node::Node (int _depth, int _i, int _j, int _loc, int _w) {
    this->n_children = 0;
    this->depth = _depth;
    this->i=_i; this->j=_j;
    this->loc = _loc;
    this->w = _w;
}


std::vector<std::vector<int>> Node::discoverLocations () {
    int line=this->state.size(), column=this->state[0].size();
    std::vector<std::vector<int>> locations;

    // Identifica as possiveis posicoes para inicio do AGV
    std::vector<int> vec2(2);
    for (j=0 ; j<column ; j++) {
        if (this->state[0][j]=='.' || this->state[0][j]=='#') {
            vec2[0]=0; vec2[1]=j;
            locations.push_back(vec2);
        }
        if (this->state[line-1][j]=='.' || this->state[line-1][j]=='#') {
            vec2[0]=line-1; vec2[1]=j;
            locations.push_back(vec2);
        }
    }
    for (i=1 ; i<(line-1) ; i++) {
        if (this->state[i][0]=='.' || this->state[i][0]=='#') {
            vec2[0]=i; vec2[1]=0;
            locations.push_back(vec2);
        }
        if (this->state[i][column-1]=='.' || this->state[i][column-1]=='#') {
            vec2[0]=i; vec2[1]=column-1;
            locations.push_back(vec2);
        }
    }

    return locations;
}


void Node::showResult (std::vector<std::vector<int>> *results) {
    int mov=99999999, ptr; 

    for (int i=0; i<(*results).size() ; i++) {
        if ((*results)[i][0] < mov) {
            mov = (*results)[i][0];
            ptr = i;
        }
    }

    std::cout << (*results)[ptr][0] << " " << (*results)[ptr][1] << " " << "[";
    std::cout << (*results)[ptr][2] << " , " << (*results)[ptr][3] << "]" << std::endl;
}


int Node::checkState (int W) {
    if (this->state[this->i][this->j]=='#') {  // Encontra um ponto de localizacao
        this->w = W;
        this->loc += 1;
        this->state[this->i][this->j] = 'X';  // Indica que a localizacao jah foi percorrida pelo AGV
        return 2;
    }
    else if (this->state[this->i][this->j]=='$') {  // Encontra um ponto de coleta
        return 1;
    }

    this->state[this->i][this->j] = 'X';  // Indica que a localizacao jah foi percorrida pelo AGV
    return 0;  // Nao encontra nenhum ponto de interesse
}


int Node::checkExplored (int i, int j, int depth, std::list<Node*> *explored) {
    std::list<Node*>::iterator it;
    for (it=(*explored).begin() ; it!=(*explored).end() ; it++) {
        if (i==(*it)->i && j==(*it)->j) {  // Se as posicoes sao iguais
            if (depth >= (*it)->depth) {  // Se o numero de passos do novo estado eh igual ou superior
                return 1;  // Caso os estados sejam iguais
            }
        }
    }

    return 0;  // Caso o estado nao tenha sido explorado
}


int Node::defineChildren (std::list<Node*> *explored, int W) {
    if (this->w < 0) {
        return 0;  // Caso o AGV nao possa fazer mais nenhum movimento
    }

    if (this->i-1>=0 && this->state[this->i-1][this->j]!='*' && this->state[this->i-1][this->j]!='X') {  // Analisando posicao ACIMA
		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorados
		if ( this->checkExplored(this->i-1, this->j, this->depth+1, explored) == 0 ) {
			this->children.push_back(new Node(this->depth+1, this->i-1, this->j, this->loc, this->w-1));
            this->children[this->children.size()-1]->state = this->state;
			this->n_children += 1;
		}
	}
    
    if (this->i+1<this->state.size() && this->state[this->i+1][this->j]!='*' && this->state[this->i+1][this->j]!='X') {  // Analisando posicao ABAIXO
		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorados
		if ( this->checkExplored(this->i+1, this->j, this->depth+1, explored) == 0 ) {
			this->children.push_back(new Node(this->depth+1, this->i+1, this->j, this->loc, this->w-1));
            this->children[this->children.size()-1]->state = this->state;
			this->n_children += 1;
		}
	}
    
    if (this->j+1<this->state[0].size() && this->state[this->i][this->j+1]!='*' && this->state[this->i][this->j+1]!='X') {  // Analisando posicao DIREITA
		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorados
		if ( this->checkExplored(this->i, this->j+1, this->depth+1, explored) == 0 ) {
			this->children.push_back(new Node(this->depth+1, this->i, this->j+1, this->loc, this->w-1));
            this->children[this->children.size()-1]->state = this->state;
			this->n_children += 1;
		}
	}
    
    if (this->j-1>=0 && this->state[this->i][this->j-1]!='*' && this->state[this->i][this->j-1]!='X') {   // Analisando posicao ESQUERDA
		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorados
		if ( this->checkExplored(this->i, this->j-1, this->depth+1, explored) == 0 ) {
			this->children.push_back(new Node(this->depth+1, this->i, this->j-1, this->loc, this->w-1));
            this->children[this->children.size()-1]->state = this->state;
			this->n_children += 1;
		}
	}

    return 0;
}


void Node::deleteChildren () {
    if (this->n_children != 0) {
		for (int i=0 ; i<this->n_children ; i++) {
			this->children[i]->deleteChildren();
			delete this->children[i];
		}
	}
}
