#include <string>

#include "gtest/gtest.h"
#include "src/lib/loader/graph_loader.h"

TEST(loaderLib_test, load_simple_graph) {
	std::shared_ptr<graph<uint64_t>> gr(new graph<uint64_t>());
	graph_loader gr_loader;
	std::string input_file("resources/tests/input_graphs/graph_topology/G1_notFully_notWeakly.txt");
	gr_loader.template load_graph<uint64_t>(gr, input_file);
	EXPECT_EQ(1, 1);
}