#pragma once
#include "IGameObject.h"
class Node;

class Edge :
	public IGameObject
{
private:
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;

	

public:
	Node*child;
	Node*parent;
	double weight;

	Edge(int xStart, int yStart, int xEnd, int yEnd );
	~Edge();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

};

