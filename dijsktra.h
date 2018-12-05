#pragma once
#include <map>
#include <limits>
#include <stack>
#include <iostream>
#include <set>
#include "CommonTypes.h"
namespace myAlgorithms {
	class DjisktraPathFind {
	public: 
		DjisktraPathFind(const std::vector<std::reference_wrapper<myAlgorithms::Node>>&);
		std::pair<std::stack<std::reference_wrapper<Node>>, int> 
			findPath(std::reference_wrapper<Node>, std::reference_wrapper<Node>);
	private:
#pragma region ALIASES
		using DistancesMap = std::map<std::reference_wrapper<Node>, std::pair<int, Node*>, SortByAddress<>>;
		using NodesSet = std::set<std::pair<std::reference_wrapper<Node>, int>, SortByDistanceFromOrigin<>>;
#pragma endregion
#pragma region FUNCTIONS
		std::pair<std::stack<std::reference_wrapper<Node>>, int>
			path(std::reference_wrapper<Node>, std::reference_wrapper<Node>);
		void cleanData();
#pragma endregion
#pragma region DATA MEMBERS
		DistancesMap distances;//all the nodes of the grap with their distances from start and previous node
		NodesSet currentNodes;//current working nodes	
		bool usedAlready;
#pragma endregion		
	};
}
