#include "AStar.h"

using namespace std;

AStar::AStar()
{

}

AStar::AStar(Node* source, Node* target)
{
	this->source = source;
	this->target = target;

	openList.insert(source);
	cameFrom[source->id] = nullptr;
}

AStar::~AStar()
{
}

float AStar::CalculateH(Node* start, Node* goal)
{
	return start->DistanceTo(goal);
}

stack<Node*> AStar::ReconstructPath(Node* current)
{
	stack<Node*> totalPath = stack<Node*>();
	totalPath.push(current);

	int id = current->id;
	while (cameFrom[id] !=nullptr)
	{
		Node* previous = cameFrom[id];
		totalPath.push(previous);
		id = previous->id;
	}
	return totalPath;
}

stack<Node*> AStar::Find()
{
	source->g_distance_to_source = 0;
	source->f_totalDistance = source->g_distance_to_source + CalculateH(source, target);

	while (!openList.empty())
	{
		Node* current = (*openList.begin());

		if (current == target)
			return ReconstructPath(target);


		openList.erase(current);
		closedList.push_back(current);

		for (int i = 0; i < current->GetEdges().size(); i++)									// Check all the node's edges
		{
			Node* next = current->GetEdges()[i]->child;											// The first edge's child node should be next node to be checked

			if (find(closedList.begin(), closedList.end(), next) != closedList.end())			// If the 'next' node is found, then continue
				continue;

			double g_Cost = current->g_distance_to_source + current->GetEdges()[i]->weight;		// Calculate the G cost for the current node by
																								// adding the distance to source along with the weight of the edge

			if (openList.find(next) == openList.end() || g_Cost < next->g_distance_to_source)	// If the next node is the same as the last one in the open list OR
			{																					// if the G cost is smaller than the distance to the source, then
				cameFrom[next->id] = current;													// log what the last node was,

				if (openList.find(next) != openList.end())										// try to find the next node in the open list and erase it,
					openList.erase(next);														

				next->g_distance_to_source = g_Cost;											// Set the G Cost for the next node,
				next->f_totalDistance = next->g_distance_to_source + CalculateH(next, target);  // Calculate and set the F value by adding the G value and the H value
																								// using the next node and the target node.

				openList.insert(next);															// insert the next node in the open list
			}
		}
	}
}

bool AStar::CompareNode::operator()(const Node* node1, const Node* node2) const
{
	if (node1 == node2) return false;
	if (node1 == nullptr) return true;
	if (node2 == nullptr) return false;

	return *node1 < *node2; // Holly shit! DO NOT FORGET THOSE POINTER ASTERICKS! OTHERWISE THE WHOLE THING WILL NOT COMPARE PROPERLY!
}