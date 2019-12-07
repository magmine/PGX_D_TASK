#include "Graph.h"
//#include "Node_Property.h"

template<class T>
void	graph<T>::add_edge(uint64_t source, uint64_t destination) {
	/*this method does not garanty that for each source we won't have any duplicate
	destinations*/
	if (graph_vertices_set.find(source) == graph_vertices_set.end()) {
		adj_list.push_back(std::list<uint64_t>());
		adj_list[graph_vertices_set.size()].push_front(destination);
		graph_vertices_set.insert(source);
		/*I can insert also destinattion if not found but it will add overheed
		what I will gain is the count of all vertices*/
		vertex_list_position_map.emplace(source, graph_vertices_set.size() - 1);
	}
	else {
		adj_list[vertex_list_position_map.find(source)->second].push_front(destination);
	}

	if (graph_vertices_set.find(destination) == graph_vertices_set.end()) {
		adj_list.push_back(std::list<uint64_t>());
		graph_vertices_set.insert(destination);
		vertex_list_position_map.emplace(destination, graph_vertices_set.size() - 1);
	}
}

template<class T>
void	graph<T>::remove_edge(uint64_t source, uint64_t destination) {
	typename std::map<uint64_t, uint64_t>::iterator it;

	it = vertex_list_position_map.find(source);
	if (it != vertex_list_position_map.end()) {
		adj_list[it->second].remove(destination);
	}
}

template<class T>
void	graph<T>::set_node_property(uint64_t n, T val) {
	property_values_map.emplace(n, val);
}

template<class T>
T	graph<T>::get_node_property(uint64_t n) {
	typename std::map<uint64_t, T>::iterator it;

	it = property_values_map.find(n);//here we supose that n is present in the graph else an exception should be handled.
	return (it->second);
}

template<class T>
std::string		graph<T>::export_node_property_to_string() {
	typename std::map<uint64_t, T>::iterator	it;
	std::ostringstream							result_string("", std::ios_base::out);
	
	it = property_values_map.begin();
	while (it != property_values_map.end()) {
		result_string << it->first << ": " << it->second << "\n";
		it++;
	}
	return result_string.str();
}

template <class T>
std::vector<uint64_t>::size_type	graph<T>::get_number_of_vertices() {
	return adj_list.size();
}

template <class T>
std::list<uint64_t>::size_type	graph<T>::get_number_of_exiting_edges_from_source(uint64_t source_pos) {
	try {
		return adj_list[source_pos].size();
	}
	catch (std::out_of_range & oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	return (0);
}


template <class T>
void		graph<T>::build_undirected_graph(std::vector<std::list<uint64_t>> &adj_list_undirected) {
	uint64_t	number_of_vertices = adj_list_undirected.size();

	std::vector<std::vector<bool>>	is_processed(number_of_vertices, std::vector<bool>(number_of_vertices, false));
	std::map<uint64_t, uint64_t>::iterator it_map = vertex_list_position_map.begin();


	for (; it_map != vertex_list_position_map.end(); it_map++) {
		std::list<uint64_t>::iterator it = adj_list[it_map->second].begin();
		uint64_t	id_source = it_map->first;

		while (it != adj_list[it_map->second].end()){
			uint64_t	pos_destination = vertex_list_position_map.find(*it)->second;
			adj_list_undirected[it_map->second].push_front(*it);
			if (!is_processed[pos_destination][it_map->second]) {
				adj_list_undirected[pos_destination].push_front(id_source);
				is_processed[pos_destination][it_map->second] = true;
			}
			it++;
		}
	}
}

template <class T>
std::set<uint64_t>	graph<T>::bfs_undirected_graph() {
	std::queue<uint64_t> que;
	std::set<uint64_t> visited_vertices_set;
	uint64_t	number_of_vertices = get_number_of_vertices();
	std::vector<std::list<uint64_t>> adj_list_undirected(number_of_vertices);
	uint64_t vertex = vertex_list_position_map.begin()->first;

	build_undirected_graph(adj_list_undirected);
	visited_vertices_set.insert(vertex);
	que.push(vertex);

	while (!que.empty()) {
		vertex = que.front();
		que.pop();
		uint64_t vertex_pos = vertex_list_position_map.find(vertex)->second;
		std::list<uint64_t>::iterator it = adj_list_undirected[vertex_pos].begin();
		do {
			if (visited_vertices_set.insert(*it).second) {
				que.push(*it);
			}
		} while (++it != adj_list_undirected[vertex_pos].end());
	}
	return visited_vertices_set;
}

template <class T>
bool								graph<T>::check_weakly_connected() {
	if (bfs_undirected_graph() == graph_vertices_set)
		return true;
	return false;
}