CXX = clang++
CXXFLAGS = -std=c++11 -Wall -pedantic
CL = rm

build:
	$(CXX) $(CXXFLAGS) main.cpp ./node/node.cpp ./algorithms/bfs.cpp ./algorithms/dfs.cpp ./algorithms/ids.cpp ./algorithms/aStar.cpp -o ./algorithms/agv

clean:
	$(CL) -rm main
