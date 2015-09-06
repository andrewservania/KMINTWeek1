
#pragma once
#include "IGameObject.h"

class Node : public IGameObject
{
public:
	Node();
	~Node();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
};

