#include "dijsktra.h"
namespace myAlgorithms {
	
	DjisktraPathFind::DjisktraPathFind(const std::vector<std::reference_wrapper<myAlgorithms::Node>>& vec) : usedAlready{ false } {
		int infinit = std::numeric_limits<int>::max();
		for (const auto& a : vec)
			distances[a] = { infinit, nullptr };
	}

	std::pair<std::stack<std::reference_wrapper<Node>>, int> DjisktraPathFind::findPath
	(std::reference_wrapper<Node> origin, std::reference_wrapper<Node> destination) {
		if(!usedAlready)
			cleanData();//case function gets called twice on same object

		//check if input is valid
		if (distances.find(origin) == distances.end() ||
			distances.find(destination) == distances.end())
			return std::make_pair(std::stack<std::reference_wrapper<Node>>(), 0);

		auto it = distances.find(destination);
		currentNodes.insert(std::make_pair( std::ref(origin.get()), 0 ));//insert origin node
		distances.at(origin) = std::make_pair(0, nullptr);

		for (NodesSet::iterator currentNodePair = currentNodes.begin(); 
			currentNodePair != currentNodes.end() && !(currentNodePair->first == it->first);//break when we reach the end or no other nodes available 
			currentNodePair = currentNodes.begin()) {

			auto& neighbourNodes = currentNodePair->first.get().otherNodes;//get neighboaring nodes of current node

			//Iterate through each neighboaring node
			for (size_t currentNodeIndex{ 0 }; currentNodeIndex < neighbourNodes.size(); currentNodeIndex++) {
				const auto& neighbourNodePair = neighbourNodes[currentNodeIndex];

				//distance from current node to origin
				int newDistance = neighbourNodePair.second + currentNodePair->second;//weight to this neighbour + current distance

				if (int distanceFromStart = distances.find(neighbourNodePair.first)->second.first;//current distance from start of neighNodePair
				newDistance < distanceFromStart){
					//if found a new shorter path to this node update it

					if (auto nodeIt = currentNodes.find(std::make_pair(neighbourNodePair.first, distanceFromStart));
					nodeIt != currentNodes.end() ) {
						//already in set, update its value
						auto temp = currentNodes.extract(nodeIt);
						temp.value().second = newDistance;
						currentNodes.insert(std::move(temp));
					}
					else//node wasnt in set
						currentNodes.insert(std::make_pair(neighbourNodePair.first, newDistance));
					
					distances.at(neighbourNodePair.first) = std::make_pair(newDistance, &currentNodePair->first.get());
			    }
			}
			currentNodes.erase(currentNodePair);
		}

		return path(origin, destination);
	}

	std::pair<std::stack<std::reference_wrapper<Node>>, int>
		myAlgorithms::DjisktraPathFind::path(std::reference_wrapper<Node> origin, std::reference_wrapper<Node> destination)	{
		auto it = distances.find(destination);
		if (it->second.second == nullptr)//no path led from start to destination
			return std::make_pair(std::stack<std::reference_wrapper<Node>>(), 0);

		std::stack<std::reference_wrapper<Node>> path;//build the path 
		
		int distance = it->second.first;
		
		for (Node* currentNode = &it->first.get(); currentNode != nullptr;
		currentNode = distances.find(std::ref(*currentNode))->second.second)//jump to previous node 
			path.push(*currentNode);
		
		return std::make_pair(path, distance);
	}

	void DjisktraPathFind::cleanData(){
		int infinit = std::numeric_limits<int>::max();
		for (auto& a : distances)
			a.second = { infinit, nullptr };

		currentNodes.clear();
	}
	
}