#include "Graph.h"
#include <memory>
#include "AStar.h"
#include <string>

using namespace std;

/// <summary>	The cow. </summary>
Cow* Graph::cow;
/// <summary>	The rabbit. </summary>
Rabbit* Graph::rabbit;
/// <summary>	The nodes. </summary>
vector<Node*> Graph::graphNodes;
/// <summary>	The shortest path label. </summary>
string Graph::shortestPathLabel;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor.
/// 			1) Create 8 nodes.
/// 			2) Set specific nodes as neighbors
/// 			3) Created egdes between these neighbors and give these edges a weight of 10000
/// 			4) Add these nodes to a vector future easy access.
/// 			  </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="_application">	[in,out] If non-null, the application. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Graph::Graph(FWApplication* _application)
{
	// Create nodes
	node1 = new Node(1);
	node2 = new Node(2);
	node3 = new Node(3);
	node4 = new Node(4);
	node5 = new Node(5);
	node6 = new Node(6);
	node7 = new Node(7);
	node8 = new Node(8);

	// Set their position on screen
	node1->SetOffset(800, 450);
	node2->SetOffset(500, 400);
	node3->SetOffset(600, 100);
	node4->SetOffset(730, 240);
	node5->SetOffset(900, 100);
	node6->SetOffset(930, 400);
	node7->SetOffset(1050, 550);
	node8->SetOffset(1050, 300);

	// Connect nodes with edges and add weight to the edges
	node1->AddEdge(node2, 10000);
	node1->AddEdge(node7, 10000);
	node1->AddEdge(node6, 10000);
	node2->AddEdge(node3, 10000);
	node2->AddEdge(node4, 10000);
	node2->AddEdge(node8, 10000);
	node3->AddEdge(node4, 10000);
	node3->AddEdge(node5, 10000);
	node4->AddEdge(node6, 10000);
	node4->AddEdge(node5, 10000);
	node5->AddEdge(node6, 10000);
	node5->AddEdge(node8, 10000);
	node7->AddEdge(node8, 10000);

	// Add the nodes to a vector
	graphNodes.push_back(node1);
	graphNodes.push_back(node2);
	graphNodes.push_back(node3);
	graphNodes.push_back(node4);
	graphNodes.push_back(node5);
	graphNodes.push_back(node6);
	graphNodes.push_back(node7);
	graphNodes.push_back(node8);

	rabbit = new Rabbit();												// Create a rabbit
	cow = new Cow();													// Create a cow

	cow->setNode(graphNodes.at(rand() % 8));							// Put the cow on a random node on the screen
	rabbit->setCurrentNode(graphNodes.at(rand() % 8));					// Put the rabbit on a random node on the screen

	while (cow->getCurrentNode()->id == rabbit->getCurrentNode()->id)	// if rabbit's current node is equal to the node of the code, pick a new node for the rabbit
		rabbit->setCurrentNode(graphNodes.at(rand() % 8));

	UpdateShortPathDescription();										// Update the shortest path label with the shortest path based on the cow and rabbit's current node
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

Graph::~Graph()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Draw the shortest path on the screen. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Graph::DrawShortPathDescription()
{
	FWApplication::GetInstance()->DrawText(shortestPathLabel, 200, 500);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Update the shortest path label on the screen.
/// </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Graph::UpdateShortPathDescription()
{
	shared_ptr<AStar> aStar = make_shared<AStar>();
	auto shortestPath = aStar->GetShortestPath(cow->getCurrentNode(), rabbit->getCurrentNode());
	shortestPathLabel = "Shortest path from cow to rabbit: ";
	while (!shortestPath.empty())
	{
		Node* step = shortestPath.top();

		shortestPathLabel += to_string(step->id).c_str();

		shortestPath.pop();
		if (!shortestPath.empty())
			shortestPathLabel += " -> ";
	}
}