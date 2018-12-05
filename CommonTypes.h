#pragma once
#include <vector>
#include <functional>

namespace myAlgorithms {
	struct Node {
		std::vector<std::pair<std::reference_wrapper<Node>, int>> otherNodes;

		Node(const std::vector<std::pair<std::reference_wrapper<Node>, int>>& neighbours) : otherNodes{ neighbours } {}
		void addNeighbour(const std::pair<std::reference_wrapper<Node>, int>& neighbour) { otherNodes.push_back(neighbour); }
		void addNeighbours(const std::vector<std::pair<std::reference_wrapper<Node>, int>>& neighbours) {
			otherNodes.reserve(otherNodes.capacity() + neighbours.size());
			otherNodes.insert(otherNodes.end(), neighbours.begin(), neighbours.end());
		}
	};
	inline bool operator==(const std::reference_wrapper<Node>& n1, const std::reference_wrapper<Node>& n2) {
		return &n1.get() == &n2.get();
	}
	
	template<class T = std::reference_wrapper<Node>>
	struct SortByAddress {
		using first_argument_type = T;
		using second_argument_type = T;
		using result_type = bool;
		bool operator()(T lhs, T rhs)const {
			return &lhs.get() <
				&rhs.get();
		}
	};

	template<class T = std::pair<std::reference_wrapper<myAlgorithms::Node>, int>>
	struct SortByDistanceFromOrigin {
		using first_argument_type = T;
		using second_argument_type = T;
		using result_type = bool;
		bool operator()(T lhs, T rhs)const {
			if (lhs.second == rhs.second)
				return SortByAddress<std::reference_wrapper<Node>>()(lhs.first, rhs.first);
			return lhs.second < rhs.second;
		}
	};

}
