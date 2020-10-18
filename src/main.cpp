/*
	TRABALHO PRATICO 01
	INTRODUCAO A INTELIGENCIA ARTIFICAL - 2020/1
*/

#include "./node/node.hpp"

#include "./algorithms/bfs.hpp"
#include "./algorithms/dfs.hpp"
#include "./algorithms/ids.hpp"
#include "./algorithms/astar.hpp"

int main(int argc, char* argv[]) {
	if (argc != 3) {
        std::cout << "Formato de entrada incorreto" << std::endl;
        return 0;
    }

	// Identifica o algoritmo a ser utilizado e o executa
	if ((std::string(argv[1])=="BFS") || (std::string(argv[1])=="bfs")) {
		BFS *bfs = new BFS(argv[2]);

		bfs->search();

		delete bfs;
	}
	else if ((std::string(argv[1])=="DFS") || (std::string(argv[1])=="dfs")) {
		DFS *dfs = new DFS(argv[2]);
		
		dfs->search();

		delete dfs;
	}
	else if ((std::string(argv[1])=="IDS") || (std::string(argv[1])=="ids")) {
		IDS *ids = new IDS(argv[2]);
		
		ids->search();

		delete ids;
	}
	else if ((std::string(argv[1])=="a_star")) {
		aStar *astar = new aStar(argv[2]);
		
		astar->search();

		delete astar;
	}

	return 0;
}
