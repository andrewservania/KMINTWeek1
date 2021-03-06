#pragma once
#include <SDL_events.h> 
#include "IGameObject.h"
#include "Node.h"

#include <stack>

class Cow :
	public IGameObject
{
private:
	bool drawRectangle;
public:
	Node* currentNode;
	std::stack<Node*> shortestPath;
	int timerCounter;
	Cow();
	~Cow();
	virtual void Update(float deltaTime) override;
	virtual void Draw()override;
	void OnClick(SDL_Event &event);
	void OnLeftClick(SDL_Event &event);
	void OnRightClick(SDL_Event &event);
	void setNode(Node* node);
	Node* getCurrentNode() { return currentNode; };
};
