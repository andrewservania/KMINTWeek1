#include "Edge.h"


Edge::Edge()
{

}

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

void Edge::Draw()
{
	mApplication->SetColor(Color(255, 0, 0, 255));
	mApplication->DrawLine(xStart, yStart, xEnd, yEnd);
	mApplication->SetColor(Color(255, 255, 255, 255));
}