#pragma once
#include "Graph.h"

class graph_algorithms {
public:
	template<typename T>
	bool is_weakly_connected(std::shared_ptr<graph<T>> g);// : Returns true if the given graph g is weakly connected
	template<typename T>
	bool is_fully_connected(std::shared_ptr<graph<T>> g);//Returns true if for every vertex vand w there isadirected edge from v to w
};
