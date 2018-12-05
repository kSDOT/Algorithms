#include "FloydPathFind.h"


namespace myAlgorithms{
	FloydPathFind::FloydPathFind(const std::vector<std::reference_wrapper<myAlgorithms::Node>>& vec) : graphSize{vec.size()}, 
		distanceOffset { 0 } {
		
		mNodeToNodeDistance.resize(graphSize);//create 2d array and make the distances in main diagonal 0
		mIntToNode.reserve(graphSize);

		for (size_t i{0}; i < graphSize; ++i){
			mNodeToNodeDistance[i].resize(graphSize);
			
			mIntToNode.push_back(vec[i]);
			mNodeToInt.emplace(std::make_pair(vec[i], i));

			//find distance from this node to others
			{
				for (size_t j{ 0 }; j < graphSize; ++j) {
					int distance = std::numeric_limits<int>::max()/2;
					Node* previous = nullptr;

					std::vector<std::pair<std::reference_wrapper<Node>, int>>& neighbours = vec[i].get().otherNodes;	
					
					for (int k{0}; k < neighbours.size(); ++k){
						if (neighbours[k].first == vec[j]){
							distance = neighbours[k].second;
							previous = &neighbours[k].first.get();
							break;
						}
					}	
					mNodeToNodeDistance[i][j] = std::make_pair( distance, previous );
				}	
				mNodeToNodeDistance[i][i] = std::make_pair( 0, &vec[i].get() );
			}			
		}

		findDistances();
	}

	std::pair<std::stack<std::reference_wrapper<Node>>, int> FloydPathFind::findPath(std::reference_wrapper<Node> origin,
		std::reference_wrapper<Node> destination) {
		//nodes not in graph
		auto originIt = mNodeToInt.find(origin);
		auto destinationIt = mNodeToInt.find(destination);

		if ( originIt == mNodeToInt.end() || destinationIt == mNodeToInt.end())
			return { std::stack<std::reference_wrapper<Node>>(), 0 };

		std::stack<std::reference_wrapper<Node>> path;

		for (Node* currentNode = &destination.get();
		currentNode != &origin.get();
		){ 
			path.push(*currentNode);
			auto temp = mNodeToInt.find(std::ref(*currentNode))->second;
			currentNode = mNodeToNodeDistance[originIt->second][temp].second;
}
		path.push(origin);

		return { path, mNodeToInt.find(destination)->second };
	}

	void FloydPathFind::findDistances(){
		for (size_t k{ 0 }; k < graphSize; ++k)
			for (size_t i{ 0 }; i < graphSize; ++i)
				for (size_t j{ 0 }; j < graphSize; ++j)
					if (mNodeToNodeDistance[i][j].first > mNodeToNodeDistance[i][k].first + mNodeToNodeDistance[k][j].first){
						mNodeToNodeDistance[i][j].first = mNodeToNodeDistance[i][k].first + mNodeToNodeDistance[k][j].first;
						mNodeToNodeDistance[i][j].second = &mIntToNode[k].get();

					}
	}

}