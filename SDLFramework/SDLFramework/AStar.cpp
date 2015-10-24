#include "AStar.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

AStar::AStar()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

AStar::~AStar()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Method responsible for calculating the shortest path between a given start node and goal node
/// The method is based on the AStar algorithm pseudo code found on Wikipedia:
/// https://en.wikipedia.org/wiki/A*_search_algorithm.
/// </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="start">	[in,out] If non-null, the start. </param>
/// <param name="goal"> 	[in,out] If non-null, the goal. </param>
///
/// <returns>	null if it fails, else the shortest path. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

stack<Node*> AStar::GetShortestPath(Node* start, Node* goal)
{
	this->source = start;																		// Set the start node
	this->target = goal;																		// Set the goal node

	openList.insert(start);																		// The set of tentative nodes to be evaluated.
	cameFrom[start->id] = nullptr;																// The map of navigated nodes.

	start->g_distance_to_source = 0;															// Cost from start along best known path.
	start->f_totalDistance = start->g_distance_to_source + CalculateH(start, goal);				// Estimated total cost from start to goal through y.

	while (!openList.empty())																	// while openset is not empty
	{
		Node* current = (*openList.begin());													// the node in openset having the lowest f_score[] value

		if (current == goal)																	// If the current node is equal to target goal,
			return ReconstructPath(goal);														// Reconstruct and return the shortest path in a stack

		openList.erase(current);																// remove from current openset
		closedList.push_back(current);															// add  current to closedset

		for (size_t i = 0; i < current->GetEdges().size(); i++)									// Check all the node's edges
		{
			Node* next = current->GetEdges()[i]->child;											// The first edge's child node should be next node to be checked

			if (find(closedList.begin(), closedList.end(), next) != closedList.end())			// If the 'next' node is found, then continue
				continue;

			float g_Cost = static_cast<float>(current->g_distance_to_source + 
				current->GetEdges()[i]->weight);												// Calculate the G cost for the current node by
																								// adding the distance to source along with the weight of the edge

			if (openList.find(next) == openList.end() || g_Cost < next->g_distance_to_source)	// If the next node is the same as the last one in the open list OR
			{																					// if the G cost is smaller than the distance to the source, then
				cameFrom[next->id] = current;													// log what the last node was,

				if (openList.find(next) != openList.end())										// try to find the next node in the open list and erase it,
					openList.erase(next);														

				next->g_distance_to_source = g_Cost;											// Set the G Cost for the next node,
				next->f_totalDistance = next->g_distance_to_source + CalculateH(next, goal);    // Calculate and set the F value by adding the G value and the H value
																								// using the next node and the target node.

				openList.insert(next);															// insert the next node in the open list
			}
		}
	}
	stack<Node*> failure;																		// If method has been unsuccessful at producing a shortest path
	return failure;																				// Return an empty stack
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculates the heuristic value between a starting node and a goal node. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="start">	[in,out] If non-null, the start. </param>
/// <param name="goal"> 	[in,out] If non-null, the goal. </param>
///
/// <returns>	The calculated h. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

float AStar::CalculateH(Node* start, Node* goal)
{
	return start->DistanceTo(goal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reconstruct the shortest path starting from the current node. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="current">	[in,out] If non-null, the current. </param>
///
/// <returns>	null if it fails, else a stack containing the shortest path. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Function call operator. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
/// 
/// overloaded function call operator in order to compare nodes
///  
/// <param name="node1">	The first node. </param>
/// <param name="node2">	The second node. </param>
///
/// <returns>	true of the first node is closer than the second node, otherwise false. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool AStar::CompareNode::operator()(const Node* node1, const Node* node2) const
{
	if (node1 == node2) return false;
	if (node1 == nullptr) return true;
	if (node2 == nullptr) return false;

	return *node1 < *node2;
}