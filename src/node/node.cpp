#include "node.hpp"


Node::Node (int dep) {
    i=0; j=0; loc=0;
	n_children = 0;
	depth = dep;
    W=0;
}

// RETORNA: 0 nao eh estado final / 1 eh estados final / 2 eh ponto de localizacao
int Node::checkState (int w) {
    if (this->state[this->i][this->j]=='$') {  // Encontra um ponto de coleta
        return 1;
    }
    else if (this->state[this->i][this->j]=='#') {  // Encontra um ponto de localizacao
        W = w;
        this->loc += 1;
        this->state[this->i][this->j] = 'X';  // Indica que a localizacao jah foi percorrida pelo AGV
        return 2;
    }

    this->state[this->i][this->j] = 'X';
    return 0;  // Nao encontra nenhum ponto de interesse
}


int Node::checkExplored (std::list<Node*> *explored) {
    std::list<Node*>::iterator it;
	for (it=(*explored).begin() ; it!=(*explored).end() ; it++) {
		for (int i=0 ; i<this->state.size() ; i++) {
			for (int j=0 ; j<this->state[0].size() ; j++) {
				if (this->state[i][j] != (*it)->state[i][j]) {
					goto diferent;
				}
			}
		}

		return 1;
		diferent: continue;
	}

    return 0;
}


int Node::defineChildren (std::list<Node*> *explored, int w) {
    // Checa se o AGV ainda pode fazer algum movimento antes de encontrar um ponto de localizacao
    if (this->W == 0) {
        return 0;
    }

	char ch;

    // Analisando posicao ACIMA - linha
    if (this->i-1>=0 && this->state[this->i-1][this->j]!='*' && this->state[this->i-1][this->j]!='X') {
		Node* new_Node1 = new Node(this->depth+1);

		new_Node1->children=this->children; new_Node1->i=this->i-1;
		new_Node1->loc=this->loc; new_Node1->j=this->j;
		new_Node1->state=this->state; new_Node1->W=this->W;
		ch = new_Node1->state[this->i-1][this->j];
		new_Node1->state[this->i-1][this->j] = 'X';

		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorados
		if ( new_Node1->checkExplored(explored) == 0 ) {
			new_Node1->state[this->i-1][this->j] = ch;
			this->children.push_back(new_Node1);
			this->n_children += 1;
			new_Node1 = NULL;
		}
		delete new_Node1;
	}

	// Analisando posicao ABAIXO - linha
	if (this->i+1<this->state.size() && this->state[this->i+1][this->j]!='*' && this->state[this->i+1][this->j]!='X') {
		Node* new_Node2 = new Node(this->depth+1);

		new_Node2->children=this->children; new_Node2->i=this->i+1;
		new_Node2->loc=this->loc; new_Node2->j=this->j;
		new_Node2->state=this->state; new_Node2->W=this->W;
		ch = new_Node2->state[this->i+1][this->j];
		new_Node2->state[this->i+1][this->j] = 'X';
		
		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorado
		if ( new_Node2->checkExplored(explored) == 0 ) {
			new_Node2->state[this->i+1][this->j] = ch;
			this->children.push_back(new_Node2);
			this->n_children += 1;
			new_Node2 = NULL;
		}
		delete new_Node2;
	}

	// Analisando posicao da DIREITA - coluna
	if (this->j+1<this->state[0].size() && this->state[this->i][this->j+1]!='*' && this->state[this->i][this->j+1]!='X') {
		Node* new_Node3 = new Node(this->depth+1);

		new_Node3->children=this->children; new_Node3->i=this->i;
		new_Node3->loc=this->loc; new_Node3->j=this->j+1;
		new_Node3->state=this->state; new_Node3->W=this->W;
		ch = new_Node3->state[this->i][this->j+1];
		new_Node3->state[this->i][this->j+1] = 'X';

		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorado
		if ( new_Node3->checkExplored(explored) == 0 ) {
			new_Node3->state[this->i][this->j+1] = ch;
			this->children.push_back(new_Node3);
			this->n_children += 1;
			new_Node3 = NULL;
		}
		delete new_Node3;
	}

	// Analisando posicao na ESQUERDA - coluna
	if (this->j-1>=0 && this->state[this->i][this->j-1]!='*' && this->state[this->i][this->j-1]!='X') {
		Node* new_Node4 = new Node(this->depth+1);

		new_Node4->children=this->children; new_Node4->i=this->i;
		new_Node4->loc=this->loc; new_Node4->j=this->j-1;
		new_Node4->state=this->state; new_Node4->W=this->W;
		ch = new_Node4->state[this->i][this->j-1];
		new_Node4->state[this->i][this->j-1] = 'X';
		
		// Verifica se o filho a ser adicionado ao atual nao eh igual a alguns dos explorado
		if ( new_Node4->checkExplored(explored) == 0 ) {
			new_Node4->state[this->i][this->j-1] = ch;
			this->children.push_back(new_Node4);
			this->n_children += 1;
			new_Node4 = NULL;
		}
		delete new_Node4;
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
