#pragma once
#include <memory>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <list>
#include <fstream>
#include <queue>
#include <mutex>
#include <thread>

template<class T>
class graph {
private:
	std::vector<std::list<uint64_t> > adj_list;
	std::map<uint64_t, T>		property_values_map;
	std::set<uint64_t>			graph_vertices_set;
	std::map<uint64_t, uint64_t> vertex_list_position_map;
public:
	//mandatory methods
	void		add_edge(uint64_t source, uint64_t destination);
	void		remove_edge(uint64_t source, uint64_t destination);
	void		set_node_property(uint64_t n, T val);
	T			get_node_property(uint64_t n);
	std::string export_node_property_to_string();

	//additional methods
	std::vector<uint64_t>::size_type	get_number_of_vertices();
	uint64_t							get_number_of_exiting_edges_from_source(uint64_t source_pos);
	bool								check_weakly_connected();
private:
	void				build_undirected_graph(std::vector<std::list<uint64_t>>& adj_list_undirected);
	std::set<uint64_t>	bfs_undirected_graph();
};