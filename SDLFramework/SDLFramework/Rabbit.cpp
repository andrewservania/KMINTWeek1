#include "Rabbit.h"


Rabbit::Rabbit()
{
	mTexture = mApplication->LoadTexture("rabbit-3.png");
	mApplication->AddRenderable(this);
	mX = 500;
	mY = 400;
}

Rabbit::~Rabbit()
{
}

void Rabbit::Update(float deltaTime)
{

}

// Draw the rabbit texture
void Rabbit::Draw()
{
	mApplication->DrawTexture(mTexture, mX, mY, 100, 100);
}

// Execute code if rabbit has been left-clicked upon
void Rabbit::OnLeftClick()
{
	printf("Left-clicked on rabbit!\n");

}

// Execute code if rabbit has been right-clicked upon
void Rabbit::OnRightClick()
{
	printf("Right-clicked on rabbit!\n");

}

void Rabbit::setCurrentNode(Node* node)
{
	currentNode = node;	
	mX = node->GetBoundingBox().x;
	mY = node->GetBoundingBox().y;
}
