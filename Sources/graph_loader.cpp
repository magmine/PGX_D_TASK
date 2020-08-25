#include "graph_loader.h"

template <class T>
void graph_loader::load_graph(std::shared_ptr<graph<T>> g, std::string file_path) {
	std::ifstream in_stream(file_path);

	if (in_stream.is_open()) {
		uint64_t source;
		uint64_t destination;
		std::string line;
		while (std::getline(in_stream, line)) {
			{
				std::stringstream ss(line);
				ss >> source >> destination;
				g->add_edge(source, destination);
			}
		}
	}
}