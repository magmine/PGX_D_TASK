#include <string>

#include "gtest/gtest.h"
#include "src/lib/loader/graph_loader.hpp"
#include "src/lib/algorithms/graph_algorithms.hpp"

TEST(algorithmsLib_test, check_connectivity) {
	graph_loader gr_loader;
	graph_algorithms gr_algorithms;
	std::shared_ptr<graph<uint64_t>> gr = std::make_shared<graph<uint64_t>>();
	std::string path_input_files("resources/tests/input_graphs/graph_topology/");

	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G1_notFully_notWeakly.txt");
	EXPECT_EQ(7, gr->get_number_of_vertices());
	EXPECT_FALSE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_FALSE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));

	gr->clear();
	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G2_notFully_Weakly.txt");
	EXPECT_EQ(7, gr->get_number_of_vertices());
	EXPECT_FALSE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_TRUE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));

	gr->clear();
	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G3_fully_weakly.txt");
	EXPECT_EQ(2, gr->get_number_of_vertices());
	EXPECT_TRUE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_TRUE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));

	gr->clear();
	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G4_fully_weakly.txt");
	EXPECT_EQ(7, gr->get_number_of_vertices());
	EXPECT_TRUE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_TRUE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));

	gr->clear();
	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G5_notFully_weakly.txt");
	EXPECT_EQ(4, gr->get_number_of_vertices());
	EXPECT_FALSE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_TRUE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));

	gr->clear();
	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G6_notFully_weakly.txt");
	EXPECT_EQ(7, gr->get_number_of_vertices());
	EXPECT_FALSE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_TRUE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));

	gr->clear();
	gr_loader.template load_graph<uint64_t>(gr, path_input_files + "G7_notFully_notWeakly.txt");
	EXPECT_EQ(8, gr->get_number_of_vertices());
	EXPECT_FALSE(gr_algorithms.template is_fully_connected<uint64_t>(gr));
	EXPECT_FALSE(gr_algorithms.template is_weakly_connected<uint64_t>(gr));
}