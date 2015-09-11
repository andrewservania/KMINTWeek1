#pragma once
#include "IGameObject.h"
class Rabbit :
	public IGameObject
{
public:
	Rabbit();
	~Rabbit();
	virtual void Update(float deltaTime) override;
	virtual void Draw()override;
	void OnLeftClick();
	void OnRightClick();
};

