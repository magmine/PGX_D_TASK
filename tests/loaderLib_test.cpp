#include <string>

#include "gtest/gtest.h"
#include "src/lib/loader/graph_loader.h"

TEST(loaderLib_test, load_simple_graph) {
	std::shared_ptr<graph<uint64_t>> gr = std::make_shared<graph<uint64_t>>();
	graph_loader gr_loader;
	std::string input_file("/home/mmaghous/coding/graph_processor/resources/tests/input_graphs/graph_topology/G1_notFully_notWeakly.txt");
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	EXPECT_EQ(7, gr->get_number_of_vertices());
}

TEST(loaderLib_test, load_multiple_graphs) {
	graph_loader gr_loader;

	std::shared_ptr<graph<uint64_t>> gr1 = std::make_shared<graph<uint64_t>>();
	std::string input_file("/home/mmaghous/coding/graph_processor/resources/tests/input_graphs/graph_topology/G1_notFully_notWeakly.txt");
	gr_loader.template load_graph<uint64_t>(gr1, input_file);
	EXPECT_EQ(7, gr1->get_number_of_vertices());

	std::shared_ptr<graph<uint64_t>> gr2 = std::make_shared<graph<uint64_t>>();
	input_file = "/home/mmaghous/coding/graph_processor/resources/tests/input_graphs/graph_topology/G3_fully_weakly.txt";
	gr_loader.template load_graph<uint64_t>(gr2, input_file);
	EXPECT_EQ(2, gr2->get_number_of_vertices());

	std::shared_ptr<graph<uint64_t>> gr3 = std::make_shared<graph<uint64_t>>();
	input_file = "/home/mmaghous/coding/graph_processor/resources/tests/input_graphs/graph_topology/G5_notFully_weakly.txt";
	gr_loader.template load_graph<uint64_t>(gr2, input_file);
	EXPECT_EQ(4, gr2->get_number_of_vertices());
}