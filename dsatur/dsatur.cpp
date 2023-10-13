#include <iostream>
#include <list>
#include <map>
#include <unordered_set>
#include <algorithm> 

#define vertices_t std::map<int, vertex*>


struct vertex {
	std::list<vertex*> neighbors;
	int index;
	int sat;
	int color = -1;
};

size_t find_biggest_degree(const vertices_t& N) {
	size_t index_biggest_degree = 0;
	for(int i = 1; i < N.size(); ++i) {
		if(N.at(i)->neighbors.size() > N.at(index_biggest_degree)->neighbors.size()){
			index_biggest_degree = i;
		}
	}
	return index_biggest_degree;
}

size_t find_biggest_sat(const vertices_t& N) {
	size_t index_biggest_sat = N.begin()->first;
	
	for(auto it = ++N.begin(); it != N.end(); ++it) {
		int index = it->first;
		vertex* curr_vertex = it->second;
		vertex* biggest_sat_vertex = N.at(index_biggest_sat);
		
		if(curr_vertex->sat > biggest_sat_vertex->sat) {
			index_biggest_sat = index;
		}
		else if(curr_vertex->sat == biggest_sat_vertex->sat) {
			if(curr_vertex->neighbors.size() > biggest_sat_vertex->neighbors.size()){
				index_biggest_sat = index;		
			}
		}
	}

	return index_biggest_sat;
}

void update_sat(vertex* v) {
	std::unordered_set<int> colors;
 	for(auto const& neighbor : v->neighbors) {
		if(neighbor->color != -1) {
			colors.insert(neighbor->color);
		}
	}
	v->sat = colors.size();
}

void color_vertex(vertex* v) {
	int color = 0;
	std::unordered_set<int> colors;
	
	
	for(vertex* n : v->neighbors) {	
		if(n->color != -1) {
			colors.insert(n->color);
		}
	}

	while(true) {
		auto it = colors.find(color);
		if(it == colors.end()){
			v->color = color;
			return;
		}
		else {
			++color;
		}
	}
}

void remove_vertex(vertices_t& N, size_t index_curr_v) {
	// Removing the node itself
 	N.erase(N.find(index_curr_v));
}

void print_adjacent_list(const vertices_t& N) {
	for(auto it = N.begin(); it != N.end(); ++it) {
		std::cout << "[" <<  it->first + 1    << "]" 
			<< "(color=" << it->second->color << ")-> ";
		for(auto const& i : it->second->neighbors) {
 		   std::cout << i->index + 1 << "->";
		}
		std::cout << std::endl;
	}
}

void dsatur(vertices_t N) {
	// Set of vertices without color
	vertices_t V(N);

	size_t index_curr_v = find_biggest_degree(V);
	
	remove_vertex(V, index_curr_v);

 	vertex* curr_v = N[index_curr_v];

 	curr_v->color = 0;

	
 	while(!V.empty()) {
 		// Update the saturation of all current vertex's neighbors that weren't colored 
 		for(vertex* v : curr_v->neighbors){
 			if(v->color == -1) {
 				update_sat(v);
 			}
 		}	

 		index_curr_v = find_biggest_sat(V);
 		curr_v = V[index_curr_v];

 		// Color vertex with the first color avaible between its neighbors
 		color_vertex(curr_v);

 		// Remove vertex after assigning a color to it
 		V.erase(V.find(index_curr_v));
 	}
}



int main(int argc, char const *argv[]) {


	size_t graph_size;
	std::cin >> graph_size;
	--graph_size;
	
	int** graph = new int*[graph_size];
	
	for(int i = 0; i < graph_size; ++i) {
		graph[i] = new int[i+1];
	}

	for(int i = 0; i < graph_size; ++i) {
		for(int j = 0; j < i+1; ++j) {
			std::cin >> graph[i][j];
		}
	}

	// Printing the matrix
	for(int i = 0; i < graph_size; ++i) {
		for(int j = 0; j < i+1; ++j) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << std::endl;
	}


	
	size_t adjacent_list_size = graph_size + 1;
	vertices_t adjacent_list;
	
	for(int i = 0; i < adjacent_list_size; ++i) {
		vertex* v = new vertex();
		v->index = i;
		//v->neighbors = new std::list<vertex*>(); 
		adjacent_list[i] = v;
	}

	
	// Reading data from matrix to write in the adjacent list
	for(int i = 0; i < graph_size; ++i) {
		for(int j = 0; j < i+1; ++j) {
			if(graph[i][j] == 1){
				adjacent_list[j]->neighbors.push_back(adjacent_list[i+1]);
				adjacent_list[i+1]->neighbors.push_back(adjacent_list[j]);	
			}
		}
	}

	dsatur(adjacent_list);

	
	// Printing adjacent list
	std::cout << "\n\nResult:" << std::endl;
	print_adjacent_list(adjacent_list);


	// TODO: free the memory of the vertices
	// Freeing the memory
	for(int i = 0; i < graph_size; ++i) {
		delete[] graph[i];
	}
	delete[] graph;
	
	return 0;
}
