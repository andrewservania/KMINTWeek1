#include "Edge.h"


Edge::Edge(int xStart, int yStart, int xEnd, int yEnd)
{
	this->xStart = xStart;
	this->xEnd = xEnd;
	this->yStart = yStart;
	this->yEnd = yEnd;
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