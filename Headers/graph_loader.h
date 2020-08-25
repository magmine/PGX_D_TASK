#pragma once
#include "Graph.h"
#include <algorithm>
#include <cstdint>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class graph_loader {
public:
	template <class T>
	void load_graph(std::shared_ptr<graph<T>> g, std::string file_path);
};
