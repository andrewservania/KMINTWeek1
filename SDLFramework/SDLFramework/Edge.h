#pragma once
#include "IGameObject.h"
class Node;

class Edge :
	public IGameObject
{
private:

public:
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
	Node*child;
	Node*parent;
	double weight;

	Edge();
	Edge(double weight, Node* parent, Node*child);
	~Edge();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
};
