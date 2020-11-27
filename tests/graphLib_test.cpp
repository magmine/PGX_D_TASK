#include <string>

#include "gtest/gtest.h"
#include "src/lib/graph/graph.hpp"

TEST(graphLib_test, create_simple_graph) {
	std::shared_ptr<graph<uint64_t>> gr(new graph<uint64_t>());
	gr->add_edge(0, 1);
	ASSERT_EQ(2, gr->get_number_of_vertices());
	gr->add_edge(1, 2);
	ASSERT_EQ(3, gr->get_number_of_vertices());
	gr->add_edge(2, 3);
	gr->add_edge(3, 4);
	gr->add_edge(4, 5);
	gr->add_edge(5, 6);
	ASSERT_EQ(7, gr->get_number_of_vertices());
	gr->add_edge(5, 4);
	gr->add_edge(5, 1);
}

TEST(DISABLE_graphLib_test, remove_edges) {
	std::shared_ptr<graph<uint64_t>> gr(new graph<uint64_t>());
	gr->add_edge(0, 1);
	gr->add_edge(1, 2);
	gr->add_edge(2, 3);
	gr->add_edge(3, 4);
	gr->add_edge(4, 5);
	gr->add_edge(5, 6);
	ASSERT_EQ(7, gr->get_number_of_vertices());
	gr->remove_edge(0, 1);
	ASSERT_EQ(6, gr->get_number_of_vertices());
	gr->remove_edge(1, 2);
	gr->remove_edge(2, 3);
	ASSERT_EQ(4, gr->get_number_of_vertices());
	gr->remove_edge(3, 4);
	gr->remove_edge(4, 5);
	ASSERT_EQ(1, gr->get_number_of_vertices());
	gr->remove_edge(5, 6);
	ASSERT_EQ(0, gr->get_number_of_vertices());
}