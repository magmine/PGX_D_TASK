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

template <class T>
void graph<T>::add_edge(uint64_t source, uint64_t destination) {
	if (graph_vertices_set.find(source) == graph_vertices_set.end()) {
		adj_list.emplace_back(std::list<uint64_t>());
		adj_list[graph_vertices_set.size()].push_front(destination);
		graph_vertices_set.insert(source);
		vertex_list_position_map.emplace(source, graph_vertices_set.size() - 1);
	} else {
		adj_list[vertex_list_position_map.find(source)->second].push_front(destination);
	}

	if (graph_vertices_set.find(destination) == graph_vertices_set.end()) {
		adj_list.emplace_back(std::list<uint64_t>());
		graph_vertices_set.insert(destination);
		vertex_list_position_map.emplace(destination, graph_vertices_set.size() - 1);
	}
}

template <class T>
void graph<T>::remove_edge(uint64_t source, uint64_t destination) {
	auto it = vertex_list_position_map.find(source);
	if (it != vertex_list_position_map.end()) {
		adj_list[it->second].remove(destination);
	}
}

template <class T>
void graph<T>::set_node_property(uint64_t n, T val) {
	property_values_map.emplace(n, val);
}

template <class T>
T graph<T>::get_node_property(uint64_t n) const {
	auto it = property_values_map.find(n);
	return (it->second);
}

template <class T>
std::string graph<T>::export_node_property_to_string() const {
	std::ostringstream result_string_stream("", std::ios_base::out);

	for (const auto& it : property_values_map) {
		result_string_stream << it.first << ": " << it.second << "\n";
	}
	return result_string_stream.str();
}

template <class T>
std::vector<uint64_t>::size_type graph<T>::get_number_of_vertices() const {
	return adj_list.size();
}

template <class T>
std::list<uint64_t>::size_type graph<T>::get_number_of_exiting_edges_from_source(uint64_t source_pos) const {
	try {
		return adj_list[source_pos].size();
	} catch (std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	return (0);
}

template <class T>
void graph<T>::build_undirected_graph(std::vector<std::list<uint64_t>>& adj_list_undirected) {
	uint64_t number_of_vertices = adj_list_undirected.size();

	/**
	 * To-do use bitset for is_processed
	*/
	std::vector<std::vector<bool>> is_processed(number_of_vertices, std::vector<bool>(number_of_vertices, false));
	std::mutex mtx;
	std::vector<std::thread> threads_to_join;

	for (const auto& it_map : vertex_list_position_map) {
		threads_to_join.emplace_back(std::thread([it_map, &is_processed, &adj_list_undirected, &mtx, this] {
			uint64_t id_source = it_map.first;

			for (const auto& it : adj_list[it_map.second]) {
				uint64_t pos_destination = vertex_list_position_map.find(it)->second;
				{
					/**
					 * Maybe use unique_guard instead
					*/
					std::lock_guard<std::mutex> locker(mtx);
					adj_list_undirected[it_map.second].push_front(it);
					if (!is_processed[pos_destination][it_map.second]) {
						adj_list_undirected[pos_destination].push_front(id_source);
						is_processed[pos_destination][it_map.second] = true;
					}
				}
			}
		}));
	}
	std::for_each(threads_to_join.begin(), threads_to_join.end(), [](std::thread& t) {
		if (t.joinable())
			t.join();
	});
}

template <class T>
std::set<uint64_t> graph<T>::bfs_undirected_graph() {
	std::queue<uint64_t> que;
	std::set<uint64_t> visited_vertices_set;
	uint64_t number_of_vertices = get_number_of_vertices();
	uint64_t vertex = vertex_list_position_map.begin()->first;
	std::mutex mtx;
	std::vector<std::thread> threads_to_join;

	std::vector<std::list<uint64_t>> adj_list_undirected(number_of_vertices);
	build_undirected_graph(adj_list_undirected);
	visited_vertices_set.insert(vertex);
	que.push(vertex);

	while (!que.empty()) {

		threads_to_join.emplace_back(std::thread([&, vertex, this]() mutable {
			if (!que.empty()) {
				std::unique_lock<std::mutex> lck(mtx);
				vertex = que.front();
				que.pop();
				lck.unlock();
				uint64_t vertex_pos = vertex_list_position_map.find(vertex)->second;
				auto it = adj_list_undirected[vertex_pos].begin();
				/**
				 * To do
				 * try to use the lock less in the do-while loop by
				 * using locking multiple iterations insted of one.
				 * */
				do {
					lck.lock();
					if (visited_vertices_set.insert(*it).second) {
						que.push(*it);
					}
					lck.unlock();
				} while (++it != adj_list_undirected[vertex_pos].end());
			}
		}));
	}

	std::for_each(threads_to_join.begin(), threads_to_join.end(), [](std::thread& t) {
		if (t.joinable()) {
			t.join();
		}
	});
	return visited_vertices_set;
}

template <class T>
bool graph<T>::check_weakly_connected() {
	if (bfs_undirected_graph() == graph_vertices_set)
		return true;
	return false;
}