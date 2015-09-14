#include "Graph.h"

using namespace std;

Cow* Graph::cow;
Rabbit* Graph::rabbit;
vector<Node*> Graph::graphNodes;
string Graph::shortPath;

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


	// Create a cow
	cow = new Cow();

	// Create a rabbit 
	rabbit = new Rabbit();

	// Put the cow on a random node on the screen
		cow->setNode(graphNodes.at(rand() % 8));
	// Put the rabbit on a random node on the screen
		rabbit->setCurrentNode(graphNodes.at(rand() % 8));

	// if rabbit's current node is equal to the node of the code, pick a new node for the rabbit
		while (cow->getCurrentNode()->id == rabbit->getCurrentNode()->id)
			rabbit->setCurrentNode(graphNodes.at(rand() % 8));

}

Graph::~Graph()
{
}

void Graph::DrawShortPathDescription()
{
	FWApplication::GetInstance()->DrawText(shortPath, 200, 500);
}