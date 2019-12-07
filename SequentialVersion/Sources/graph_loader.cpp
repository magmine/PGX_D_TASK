#include "graph_loader.h"

template<class T>
void graph_loader::load_graph(std::shared_ptr<graph<T> > g, std::string file_path) {
	std::ifstream	in_stream(file_path);

	//in_stream.open(file_path);
	if (in_stream.is_open()) {
		uint64_t	source;
		uint64_t	destination;
		std::string		line;
		while (std::getline(in_stream, line)) {
			std::stringstream		ss(line); //this is a bas practice since I'm calling constructur multiple times;
			ss >> source >> destination; //some errors can be generated here
			g->add_edge(source, destination);
		}
	}
}