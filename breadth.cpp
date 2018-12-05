#include "breadth.h"
namespace myAlgorithms {
	void BreadthFirstIteration::iterateGraph
	(std::reference_wrapper<Node> origin, const std::function<void(std::reference_wrapper<Node>)>& cb){
		visitedNodes.clear();//case function gets called twice on same object
					
		nodesQueue.push(origin.get());//insert origin node
		visitedNodes.insert(origin);
		
		for (auto currentNode = nodesQueue.front(); nodesQueue.size() != 0; ) {
			currentNode = nodesQueue.front();
			nodesQueue.pop();
			
			if(cb)
				cb(currentNode);
			
			for ( auto& neighbourNodePair : currentNode.get().otherNodes)
				if ( std::reference_wrapper<Node> node = neighbourNodePair.first; visitedNodes.find(node) == visitedNodes.end()){
					//haven't been to this node yet, add it to visited and queue
					visitedNodes.insert(node);
					nodesQueue.push(node);
				}
		}
	}


}