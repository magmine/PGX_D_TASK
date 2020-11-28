#include <string>

#include "gtest/gtest.h"
#include "src/lib/loader/graph_loader.hpp"

TEST(loaderLib_test, load_simple_graph) {
	std::shared_ptr<graph<uint64_t>> gr = std::make_shared<graph<uint64_t>>();
	graph_loader gr_loader;
	std::string input_file("resources/tests/input_graphs/graph_topology/G1_notFully_notWeakly.txt");
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	EXPECT_EQ(7, gr->get_number_of_vertices());
}

TEST(loaderLib_test, load_multiple_graphs) {
	graph_loader gr_loader;

	std::shared_ptr<graph<uint64_t>> gr = std::make_shared<graph<uint64_t>>();
	std::string input_file("resources/tests/input_graphs/graph_topology/G1_notFully_notWeakly.txt");
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	EXPECT_EQ(7, gr->get_number_of_vertices());

	gr->clear();
	input_file = "resources/tests/input_graphs/graph_topology/G3_fully_weakly.txt";
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	EXPECT_EQ(2, gr->get_number_of_vertices());

	gr->clear();
	input_file = "resources/tests/input_graphs/graph_topology/G5_notFully_weakly.txt";
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	EXPECT_EQ(4, gr->get_number_of_vertices());
}