#pragma once
#include "IGameObject.h"
class Edge :
	public IGameObject
{
private:
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;

public:
	Edge(int xStart, int yStart, int xEnd, int yEnd );
	~Edge();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

};

