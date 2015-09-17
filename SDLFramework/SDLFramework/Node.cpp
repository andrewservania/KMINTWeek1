#include "Node.h"
#include <string>


Node::Node(int id)
{
	this->id = id;
	SetOffset(50,50);
	SetSize(10, 10);

	mApplication->AddRenderable(this);		// Immediately add a node when it is initialized
											// Benefit: No need to separately add nodes later on
}


Node::~Node()
{
}

void Node::Update(float deltaTime)
{

	
}

//Responsible for drawing a colored rectangle on the screen
void Node::Draw()
{
	//Thumb rule: Set the color then re SET the color as background color again!
	//SDL work by a coloring on layer basis
	mApplication->SetColor(Color(0, 0 , 255, 255));
	mApplication->DrawRect(mX, mY, mWidth, mHeight, true);
	mApplication->DrawText(std::to_string(id), this->mX, this->mY-60);

	mApplication->SetColor(Color(255, 255, 255, 255));
}

std::vector<Edge*> Node::GetEdges()
{
	return edges;
}

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
	if (createEdge)	child->AddEdge(this,weight);

	return this;
}