#pragma once
#include "IGameObject.h"
#include "Edge.h"

class Node : public IGameObject
{
private:
	std::vector<Edge*> edges;

public:
	int id;
	float g_distance_to_source;
	float f_totalDistance;

	Node(int id);
	~Node();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	std::vector<Edge*> GetEdges();
	Node* AddEdge(Node* child, int weight);
	bool operator < (const Node& _node) const{
		if (f_totalDistance != _node.f_totalDistance) return f_totalDistance < _node.f_totalDistance;

		if (mX == _node.mX)
		{
			return mY < _node.mY;
		}
		return mX < _node.mX;
	}
};
