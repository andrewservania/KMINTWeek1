#pragma once
#include "IGameObject.h"
#include "Node.h"

class Cow :
	public IGameObject
{
public:
	Node* currentNode;

	Cow();
	~Cow();
	virtual void Update(float deltaTime) override;
	virtual void Draw()override;
	void OnLeftClick();
	void OnRightClick();
	void setNode(Node* node);
	Node* getCurrentNode() { return currentNode; };
};

