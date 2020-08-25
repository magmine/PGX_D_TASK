#include "graph_algorithms.h"

template <typename T>
bool graph_algorithms::is_weakly_connected(std::shared_ptr<graph<T>> g) {
	if (is_fully_connected(g))
		return true;
	return g->check_weakly_connected();
}

template <typename T>
bool graph_algorithms::is_fully_connected(std::shared_ptr<graph<T>> g) {
	std::vector<uint64_t>::size_type number_of_vertices = g->get_number_of_vertices();
	std::list<uint64_t>::size_type number_of_edges = 0;

	for (uint64_t i = 0; i < number_of_vertices; i++) {
		number_of_edges = g->get_number_of_exiting_edges_from_source(i);
		if (number_of_edges < (number_of_vertices - 1))
			return false;
	}
	return true;
}