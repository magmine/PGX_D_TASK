#include <string>

#include "gtest/gtest.h"
#include "src/lib/loader/graph_loader.hpp"
#include "src/lib/algorithms/graph_algorithms.hpp"

TEST(algorithmsLib_test, is_weakly_connected) {
	graph_loader gr_loader;
	graph_algorithms gr_algorithms;
	//std::shared_ptr<graph<uint64_t>> gr = std::make_shared<graph<uint64_t>>();
	std::shared_ptr<graph<uint64_t>> gr(new graph<uint64_t>());
	std::string input_file("resources/tests/input_graphs/graph_topology/G1_notFully_notWeakly.txt");
	gr_loader.template load_graph<uint64_t>(gr, input_file);

	EXPECT_EQ(7, gr->get_number_of_vertices());
	EXPECT_FALSE(gr_algorithms.is_weakly_connected(gr));
}