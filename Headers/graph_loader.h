#ifndef GRAPH_LOADER_H
#define GRAPH_LOADER_H

#include <memory>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <forward_list>
#include <fstream>
#include "Graph.h"

class graph_loader {
public:
	template<class T>
	void load_graph(std::shared_ptr<graph<T>> g, std::string file_path);
};

template<class T>
void graph_loader::load_graph(std::shared_ptr<graph<T> > g, std::string file_path) {
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
	} else {
		throw std::invalid_argument("Not able to load the graph, file not found\n");
	}
}

#endif