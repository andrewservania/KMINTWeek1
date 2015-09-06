#include "Node.h"


Node::Node()
{
	SetOffset(50,50);
	SetSize(10, 10);

	
}


Node::~Node()
{
}

void Node::Update(float deltaTime)
{

	
}

//Responsible for drawing a colored rectangle on the screen
void Node::Draw()
{
	//Thumb rule: Set the color then re SET the color as background color again!
	//SDL work by a coloring on layer basis
	mApplication->SetColor(Color(0, 0 , 255, 255));
	mApplication->DrawRect(mX, mY, mWidth, mHeight, true);
	mApplication->SetColor(Color(255, 255, 255, 255));
}