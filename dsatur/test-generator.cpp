#include <iostream>
#include <random>
#include <cstdlib>
#include <fstream>  
#include <sstream>

int main(int argc, char const *argv[]) {

	
 	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 100);

    int probability = std::atoi(argv[2]);

	size_t graph_size = std::atoi(argv[1]) - 1;
	
	int** graph = new int*[graph_size];
	
	for(int i = 0; i < graph_size; ++i) {
		graph[i] = new int[i+1];
	}

	for(int i = 0; i < graph_size; ++i) {
		for(int j = 0; j < i+1; ++j) {
			int randomNumber = distrib(gen);

			graph[i][j] = (int)(randomNumber <= probability);
		}
	}


	std::stringstream file_name;
	file_name << "test-size-" << graph_size + 1 << "-probability-" << probability << ".txt";
	std::ofstream of(file_name.str());

	// Printing the matrix in the standard output and writing into a file
	std::cout << graph_size + 1 << std::endl;;
	of << graph_size + 1 << std::endl;;
	for(int i = 0; i < graph_size; ++i) {
		for(int j = 0; j < i+1; ++j) {
			std::cout << graph[i][j] << " ";
			of << graph[i][j] << " ";
		}
		std::cout << std::endl;
		of << std::endl;
	}

	of.close();


	

	// Freeing the memory
	for(int i = 0; i < graph_size; ++i) {
		delete[] graph[i];
	}
	delete[] graph;

	
	return 0;
}