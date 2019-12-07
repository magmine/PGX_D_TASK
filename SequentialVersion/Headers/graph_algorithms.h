#pragma once
#include "Graph.h"

class graph_algorithms {
public:
	template<typename T>
	bool is_weakly_connected(std::shared_ptr<graph<T>> g);// : Returns true if the given graph g is weakly connected
	template<typename T>
	bool is_fully_connected(std::shared_ptr<graph<T>> g);//Returns true if for every vertex vand w there isadirected edge from v to w
};

/*
Notes:
	!!The concept of fully and weakly connected graphs is defined only for directed graphs.
		-> A graph is concidered connected if there is a path between each pair of vertices.
		-> A graph is fully connected if there as an edge between all pairs of vertices.
		-> A directed graph is weakly connected if replacing all of its directed edges with undirected edges produces a connected (undirected) graph.
		-> A graph is strongly connected if there is a directed path between each pair of vertvices.
*/