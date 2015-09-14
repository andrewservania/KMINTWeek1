#include "Edge.h"


Edge::Edge()
{

}

// Create edge based on a parent node and a child node and add it to render able objects 
Edge::Edge(double weight, Node* parent, Node* child)
{
	this->weight = weight;
	this->parent = parent;
	this->child = child;
	mApplication->AddRenderable(this);
}

Edge::~Edge()
{
}

void Edge::Update(float deltaTime)
{
}

// Draw the actual edge on screen
void Edge::Draw()
{
	mApplication->SetColor(Color(255, 0, 0, 255));
	mApplication->DrawLine(xStart, yStart, xEnd, yEnd);
	mApplication->SetColor(Color(255, 255, 255, 255));
}