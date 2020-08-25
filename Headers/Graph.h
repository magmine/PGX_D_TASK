#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

template <class T>
class graph {
private:
	std::vector<std::list<uint64_t>> adj_list;
	std::map<uint64_t, T> property_values_map;
	std::set<uint64_t> graph_vertices_set;
	std::map<uint64_t, uint64_t> vertex_list_position_map;

public:
	//mandatory methods
	void add_edge(uint64_t source, uint64_t destination);
	void remove_edge(uint64_t source, uint64_t destination);
	void set_node_property(uint64_t n, T val);
	T get_node_property(uint64_t n) const;
	std::string export_node_property_to_string() const;

	//additional methods
	std::vector<uint64_t>::size_type get_number_of_vertices() const;
	uint64_t get_number_of_exiting_edges_from_source(uint64_t source_pos) const;
	bool check_weakly_connected();

private:
	void build_undirected_graph(std::vector<std::list<uint64_t>>& adj_list_undirected);
	std::set<uint64_t> bfs_undirected_graph();
};