#pragma once
#include "IGameObject.h"

class Cow :
	public IGameObject
{
public:
	

	Cow();
	~Cow();
	virtual void Update(float deltaTime) override;
	virtual void Draw()override;
	void OnLeftClick();
	void OnRightClick();
};

