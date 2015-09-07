
#pragma once
#include "IGameObject.h"
#include "Edge.h"


class Node : public IGameObject
{
public:
	int id;
	int g_distance_to_source;
	int f_totalDistance;
	std::vector<Edge*> edges;

	Node();
	~Node();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	std::vector<Edge*> GetEdges();
};

