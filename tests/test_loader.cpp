#include "gtest/gtest.h"
#include "Graph.h"
#include "graph_algorithms.h"
#include "graph_loader.h"

int main(int argc, char **args)
{
    ::testing::InitGoogleTest(&argc, args);
    return RUN_ALL_TESTS();
}

TEST(loader_load_graph, loader_load_graph_Test)
{
    std::shared_ptr<graph<uint64_t> > gr(new graph<uint64_t>());
	graph_loader gr_loader;
	graph_algorithms gr_algorithms;
	std::string input_file("../../Input/G1_notFully_notWeakly.txt");
	//std::ifstream 	value_in("G1_value_in.txt");
	try {
        gr_loader.template load_graph<uint64_t>(gr, input_file);
    } catch (std::exception &e){
        std::cerr<<e.what()<<"\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Exporting graph properties to string:\n\n";
	std::cout << gr->export_node_property_to_string()<<"\n";
}