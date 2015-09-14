#pragma once
#include "IGameObject.h"
#include "Node.h"

class Rabbit :
	public IGameObject
{
public:
	Node* currentNode;
	Rabbit();
	~Rabbit();
	virtual void Update(float deltaTime) override;
	virtual void Draw()override;
	void OnLeftClick();
	void OnRightClick();
	void setCurrentNode(Node* node);
	Node* getCurrentNode() { return currentNode; }
};

