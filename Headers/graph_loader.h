#pragma once
#include <memory>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <forward_list>
#include <fstream>
#include "Graph.h"

class graph_loader {
public:
	template<class T>
	void load_graph(std::shared_ptr<graph<T>> g, std::string file_path);
};
