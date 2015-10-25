#include "Node.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
///  Create a node by providing an ID and add it to items that should be shown on screen
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="id">	The identifier. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Node::Node(int id)
{
	this->id = id;
	SetOffset(50, 50);
	SetSize(10, 10);

	mApplication->AddRenderable(this);		// Immediately add a node when it is initialized
	// Benefit: No need to separately add nodes later on
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

Node::~Node()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates the node with a given deltaTime. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="deltaTime">	The delta time. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Node::Update(float deltaTime)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Responsible for drawing a colored rectangle on the screen. </summary>
///  Thumb rule: Set the color then re SET the color as background color again!
/// <remarks>	Andrew Servania,. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Node::Draw()
{
	//Thumb rule: Set the color then re SET the color as background color again!
	//SDL work by a coloring on layer basis
	mApplication->SetColor(Color(0, 0, 255, 255));
	mApplication->DrawRect(mX, mY, mWidth, mHeight, true);
	mApplication->DrawText(std::to_string(id), this->mX, this->mY - 60);

	mApplication->SetColor(Color(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Gets the edges of the node. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <returns>	null if it fails, else the edges. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<Edge*> Node::GetEdges()
{
	return edges;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Adds an edge to 'weight'. </summary>
///
/// <remarks>	Andrew Servania,. </remarks>
///
/// <param name="child"> 	[in,out] If non-null, the child. </param>
/// <param name="weight">	The weight. </param>
///
/// <returns>	null if it fails, else a Node*. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

Node* Node::AddEdge(Node* child, int weight)
{
	Edge* edge = new Edge(weight, this, child);

	edge->xStart = this->mX;
	edge->yStart = this->mY;

	edge->xEnd = child->mX;
	edge->yEnd = child->mY;

	edges.push_back(edge);

	// Check if edge already exists
	bool createEdge = true;
	if (!child->GetEdges().empty())
	{
		for (auto e : child->GetEdges())
		{
			if (e->parent == child && e->child == this)
				createEdge = false;
		}
	}

	// If edge does not exists, add new edge
	if (createEdge)	child->AddEdge(this, weight);

	return this;
}