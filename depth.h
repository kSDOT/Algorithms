#pragma once
#include  "CommonTypes.h"
#include <stack>
#include <set>
namespace myAlgorithms {
	class DepthFirstIteration {
	public:
		DepthFirstIteration() = default;
		void iterateGraph(std::reference_wrapper<Node>,
						  const std::function<void(std::reference_wrapper<Node>)>& = nullptr);
	private:
#pragma region ALIASES
		using VisitedSet = std::set<std::reference_wrapper<Node>, SortByAddress<>>;
		using NodeStack = std::stack<std::reference_wrapper<Node>>;
#pragma endregion
#pragma region DATA MEMBERS
		VisitedSet visitedNodes;//place the nodes we are done with here so we dont visit twice
		NodeStack nodesStack;//current working nodes	
#pragma endregion		
	};
}