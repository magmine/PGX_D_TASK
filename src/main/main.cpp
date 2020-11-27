#include <fstream>

#include "../lib/algorithms/graph_algorithms.h"
#include "../lib/graph/graph.h"
#include "../lib/loader/graph_loader.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: ./solution input_file.txt\n";
		return -1;
	}
	std::shared_ptr<graph<uint64_t>> gr = std::make_shared<graph<uint64_t>>();
	graph_loader gr_loader;
	graph_algorithms gr_algorithms;
	std::string input_file(argv[1]);
	//std::ifstream 	value_in("G1_value_in.txt");

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
	return 0;
}
