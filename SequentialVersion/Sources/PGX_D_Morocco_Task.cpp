#include "Graph.h"
#include "graph_loader.h"
#include "Graph.cpp"
#include "graph_loader.cpp"
#include "graph_algorithms.h"
#include "graph_algorithms.cpp"
#include <fstream>

int main() {
	std::shared_ptr<graph<uint64_t> > gr(new graph<uint64_t>());
	graph_loader gr_loader;
	graph_algorithms gr_algorithms;
	std::string input_file("C:\\Users\\Amin\\source\\repos\\PGX_D_Morocco_Task\\PGX_D_Morocco_Task\\Sources\\G7_notFully_notWeakly.txt");
	//std::ifstream value_in("C:\\Users\\Amin\\source\\repos\\PGX_D_Morocco_Task\\PGX_D_Morocco_Task\\Sources\\G1_value_in.txt");
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	/*if (!value_in.is_open())
		return 0;
	std::string line;
	while (std::getline(value_in, line)) {
		std::stringstream ss(line);
		uint64_t source, value;
		ss >> source >> value;
		gr->set_node_property(source, value);
	}
	std::cout << "Exporting graph properties to string:\n\n";
	std::cout << gr->export_node_property_to_string()<<"***********\n";*/
	std::cout << "\nis fully connected ?\n";
	if (gr_algorithms.is_fully_connected(gr))
		std::cout << "Yes\n";
	else
		std::cout << "No\n";

	std::cout << "\nis weakly connected ?\n";
	if (gr_algorithms.is_weakly_connected(gr))
		std::cout << "Yes\n";
	else
		std::cout << "No\n";

	std::cin >> input_file;
	return 0;
}