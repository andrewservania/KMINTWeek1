#pragma once
#include "Node.h"
#include <stack>
#include <set>
#include <map>

class AStar
{
public:
	AStar();

	~AStar();

	std::stack<Node*> GetShortestPath(Node* source, Node* target);

private:
	Node* source;
	Node* target;

	float CalculateH(Node* start, Node* goal);
	std::stack<Node*> ReconstructPath(Node* current);

	class CompareNode
	{
		public: 
			bool operator() (const Node*, const Node*) const;
	};

	std::set<Node*, CompareNode> openList;
	std::vector<Node*> closedList;								// The set of nodes already evaluated
	std::map<int, Node*> cameFrom;
};

