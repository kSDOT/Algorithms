#pragma once
#include  "CommonTypes.h"
#include <queue>
#include <vector>
#include <set>
namespace myAlgorithms {
	class BreadthFirstIteration {
	public:
		BreadthFirstIteration() = default;
		void iterateGraph(std::reference_wrapper<Node>,
			const std::function<void(std::reference_wrapper<Node>)>& = nullptr);
	private:
#pragma region ALIASES
		using VisitedSet = std::set<std::reference_wrapper<Node>, SortByAddress<>>;
		using NodeQueue = std::queue<std::reference_wrapper<Node>>;
#pragma endregion
#pragma region DATA MEMBERS
		VisitedSet visitedNodes;//place the nodes we are done with here so we dont visit again
		NodeQueue nodesQueue;//current working nodes
#pragma endregion		
	};
}