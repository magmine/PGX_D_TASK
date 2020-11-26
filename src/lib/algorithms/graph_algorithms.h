#pragma once
#include "../graph/graph.h"

class graph_algorithms {
public:
	template <typename T>
	bool is_weakly_connected(std::shared_ptr<graph<T>> g); // : Returns true if the given graph g is weakly connected
	template <typename T>
	bool is_fully_connected(std::shared_ptr<graph<T>> g); //Returns true if for every vertex vand w there isadirected edge from v to w
};

template <typename T>
bool graph_algorithms::is_weakly_connected(std::shared_ptr<graph<T>> g) {
	if (is_fully_connected(g))
		return true;
	return g->check_weakly_connected();
}

template <typename T>
bool graph_algorithms::is_fully_connected(std::shared_ptr<graph<T>> g) {
	std::size_t number_of_vertices = g->get_number_of_vertices();
	std::size_t number_of_edges = 0;

	for (std::size_t i = 0; i < number_of_vertices; i++) {
		number_of_edges = g->get_number_of_exiting_edges_from_source(i);
		if (number_of_edges < number_of_vertices)
			return false;
	}
	return true;
}
