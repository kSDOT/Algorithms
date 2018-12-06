#pragma once
#include "CommonTypes.h"
#include <algorithm>
#include <map>
#include <stack>
namespace myAlgorithms{
	class FloydPathFind
	{
	public:
		FloydPathFind(const std::vector<std::reference_wrapper<myAlgorithms::Node>>&);	
		std::pair<std::stack<std::reference_wrapper<Node>>, int>
			findPath(std::reference_wrapper<Node>, std::reference_wrapper<Node>);
	private:
		void findDistances();
		std::vector<std::vector<std::pair<int, Node*>>> mNodeToNodeDistance;

		std::map<std::reference_wrapper<myAlgorithms::Node>, int, SortByAddress<>> mNodeToInt;
		std::vector<std::reference_wrapper<myAlgorithms::Node>> mIntToNode;
		unsigned int graphSize;
	};
}